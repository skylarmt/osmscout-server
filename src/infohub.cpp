#include "infohub.h"
#include <QMutexLocker>

InfoHub infoHub;

InfoHub::InfoHub(QObject *parent) : QObject(parent)
{

}

void InfoHub::setError(bool e)
{
    infoHub.impSetError(e);
}

void InfoHub::impSetError(bool e)
{
    bool ce;
    {
        QMutexLocker lk(&m_mutex);
        ce = m_error;
        m_error =  e;
    }
    if (ce != e)
        emit errorChanged(e);
}

bool InfoHub::error()
{
    QMutexLocker lk(&m_mutex);
    return m_error;
}

void InfoHub::logError(const QString &txt)
{
    infoHub.impLogError(txt);
}

void InfoHub::logWarning(const QString &txt)
{
    infoHub.impLogWarning(txt);
}

void InfoHub::logInfo(const QString &txt)
{
    infoHub.impLogInfo(txt);
}

void InfoHub::impLogError(const QString &txt)
{
    emit error(txt);
    emit log(tr("ERROR: ") + txt);
}

void InfoHub::impLogWarning(const QString &txt)
{
    emit warning(txt);
    emit log(tr("WARNING: ") + txt);
}

void InfoHub::impLogInfo(const QString &txt)
{
    emit warning(txt);
    emit log(tr("INFO: ") + txt);
}