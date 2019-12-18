#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct TYPE_10__ {int fd; struct TYPE_10__* prev; struct TYPE_10__* next; TYPE_2__* pThreadObj; } ;
struct TYPE_9__ {int numOfThreads; int /*<<< orphan*/  label; TYPE_2__* pThreadObj; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  numOfFds; int /*<<< orphan*/  threadId; int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  fdReady; TYPE_4__* pHead; int /*<<< orphan*/  pollFd; } ;
typedef  TYPE_2__ SThreadObj ;
typedef  TYPE_3__ SServerObj ;
typedef  TYPE_4__ SFdObj ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLWAKEUP ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tError (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int taosOpenUDServerSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_4__*) ; 

void taosAcceptUDConnection(void *arg) {
  int                connFd = -1;
  int                sockFd;
  int                threadId = 0;
  SThreadObj *       pThreadObj;
  SServerObj *       pServerObj;
  SFdObj *           pFdObj;
  struct epoll_event event;

  pServerObj = (SServerObj *)arg;
  sockFd = taosOpenUDServerSocket(pServerObj->ip, pServerObj->port);

  if (sockFd < 0) {
    tError("%s failed to open UD socket, ip:%s, port:%u", pServerObj->label, pServerObj->ip, pServerObj->port);
    return;
  } else {
    tTrace("%s UD server is ready, ip:%s, port:%u", pServerObj->label, pServerObj->ip, pServerObj->port);
  }

  while (1) {
    connFd = accept(sockFd, NULL, NULL);

    if (connFd < 0) {
      tError("%s UD accept failure, errno:%d, reason:%s", pServerObj->label, errno, strerror(errno));
      continue;
    }

    // pick up the thread to handle this connection
    pThreadObj = pServerObj->pThreadObj + threadId;

    pFdObj = (SFdObj *)malloc(sizeof(SFdObj));
    if (pFdObj == NULL) {
      tError("%s no enough resource to allocate TCP FD IDs", pServerObj->label);
      close(connFd);
      continue;
    }

    memset(pFdObj, 0, sizeof(SFdObj));
    pFdObj->fd = connFd;
    pFdObj->pThreadObj = pThreadObj;

    event.events = EPOLLIN | EPOLLPRI | EPOLLWAKEUP;
    event.data.ptr = pFdObj;
    if (epoll_ctl(pThreadObj->pollFd, EPOLL_CTL_ADD, connFd, &event) < 0) {
      tError("%s failed to add UD FD for epoll, error:%s", pServerObj->label, strerror(errno));
      tfree(pFdObj);
      close(connFd);
      continue;
    }

    // notify the data process, add into the FdObj list
    pthread_mutex_lock(&(pThreadObj->threadMutex));

    pFdObj->next = pThreadObj->pHead;

    if (pThreadObj->pHead) (pThreadObj->pHead)->prev = pFdObj;

    pThreadObj->pHead = pFdObj;

    pThreadObj->numOfFds++;
    pthread_cond_signal(&pThreadObj->fdReady);

    pthread_mutex_unlock(&(pThreadObj->threadMutex));

    tTrace("%s UD thread:%d, a new connection, numOfFds:%d", pServerObj->label, pThreadObj->threadId,
           pThreadObj->numOfFds);

    // pick up next thread for next connection
    threadId++;
    threadId = threadId % pServerObj->numOfThreads;
  }
}