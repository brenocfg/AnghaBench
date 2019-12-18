#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_9__ {TYPE_4__* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  clientAddr ;
struct TYPE_12__ {int fd; struct TYPE_12__* prev; struct TYPE_12__* next; TYPE_2__* pThread; int /*<<< orphan*/  ipstr; } ;
struct TYPE_11__ {int online; int numOfThreads; TYPE_2__* pThreads; int /*<<< orphan*/  label; int /*<<< orphan*/  serverPort; int /*<<< orphan*/  serverIp; } ;
struct TYPE_10__ {int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  fdReady; scalar_t__ numOfFds; TYPE_4__* pHead; int /*<<< orphan*/  pServer; int /*<<< orphan*/  label; int /*<<< orphan*/  pollFd; } ;
typedef  TYPE_2__ HttpThread ;
typedef  TYPE_3__ HttpServer ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EPOLLWAKEUP ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ accept (int,struct sockaddr*,int*) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* httpCreateContext (TYPE_3__*) ; 
 int /*<<< orphan*/  httpError (char*,...) ; 
 int /*<<< orphan*/  httpFreeContext (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  httpPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int,char*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCloseSocket (int) ; 
 int /*<<< orphan*/  taosKeepTcpAlive (int) ; 
 int taosOpenTcpServerSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSetNonblocking (int,int) ; 
 int /*<<< orphan*/  tclose (int) ; 
 int tsHttpCacheSessions ; 

void httpAcceptHttpConnection(void *arg) {
  int                connFd = -1;
  struct sockaddr_in clientAddr;
  int                sockFd;
  int                threadId = 0;
  HttpThread *       pThread;
  HttpServer *       pServer;
  HttpContext *      pContext;
  int                totalFds;

  pServer = (HttpServer *)arg;

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGPIPE);
  pthread_sigmask(SIG_SETMASK, &set, NULL);

  sockFd = taosOpenTcpServerSocket(pServer->serverIp, pServer->serverPort);

  if (sockFd < 0) {
    httpError("http server:%s, failed to open http socket, ip:%s:%u", pServer->label, pServer->serverIp,
              pServer->serverPort);
    return;
  } else {
    httpPrint("http service init success at ip:%s:%u", pServer->serverIp, pServer->serverPort);
    pServer->online = true;
  }

  while (1) {
    socklen_t addrlen = sizeof(clientAddr);
    connFd = (int)accept(sockFd, (struct sockaddr *)&clientAddr, &addrlen);

    if (connFd < 3) {
      httpError("http server:%s, accept connect failure, errno:%d, reason:%s", pServer->label, errno, strerror(errno));
      continue;
    }

    totalFds = 1;
    for (int i = 0; i < pServer->numOfThreads; ++i) {
      totalFds += pServer->pThreads[i].numOfFds;
    }

    if (totalFds > tsHttpCacheSessions * 20) {
      httpError("fd:%d, ip:%s:%u, totalFds:%d larger than httpCacheSessions:%d*20, refuse connection",
              connFd, inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port), totalFds, tsHttpCacheSessions);
      taosCloseSocket(connFd);
      continue;
    }

    taosKeepTcpAlive(connFd);
    taosSetNonblocking(connFd, 1);

    // pick up the thread to handle this connection
    pThread = pServer->pThreads + threadId;

    pContext = httpCreateContext(pServer);
    if (pContext == NULL) {
      httpError("fd:%d, ip:%s:%u, no enough resource to allocate http context", connFd, inet_ntoa(clientAddr.sin_addr),
                htons(clientAddr.sin_port));
      taosCloseSocket(connFd);
      continue;
    }

    httpTrace("context:%p, fd:%d, ip:%s:%u, thread:%s, numOfFds:%d, totalFds:%d, accept a new connection",
            pContext, connFd, inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port), pThread->label,
            pThread->numOfFds, totalFds);

    pContext->fd = connFd;
    sprintf(pContext->ipstr, "%s:%d", inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port));
    pContext->pThread = pThread;

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLPRI | EPOLLWAKEUP | EPOLLERR | EPOLLHUP | EPOLLRDHUP;

    event.data.ptr = pContext;
    if (epoll_ctl(pThread->pollFd, EPOLL_CTL_ADD, connFd, &event) < 0) {
      httpError("context:%p, fd:%d, ip:%s:%u, thread:%s, failed to add http fd for epoll, error:%s",
                pContext, connFd, inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port), pThread->label,
                strerror(errno));
      httpFreeContext(pThread->pServer, pContext);
      tclose(connFd);
      continue;
    }

    // notify the data process, add into the FdObj list
    pthread_mutex_lock(&(pThread->threadMutex));

    pContext->next = pThread->pHead;

    if (pThread->pHead) (pThread->pHead)->prev = pContext;

    pThread->pHead = pContext;

    pThread->numOfFds++;
    pthread_cond_signal(&pThread->fdReady);

    pthread_mutex_unlock(&(pThread->threadMutex));

    // pick up next thread for next connection
    threadId++;
    threadId = threadId % pServer->numOfThreads;
  }
}