#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_6__ {int numOfThreads; char* label; int /*<<< orphan*/  serverPort; int /*<<< orphan*/  serverIp; int /*<<< orphan*/  thread; int /*<<< orphan*/  processData; TYPE_1__* pThreads; } ;
struct TYPE_5__ {char* label; int threadId; scalar_t__ pollFd; int /*<<< orphan*/  thread; int /*<<< orphan*/  fdReady; int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  processData; TYPE_2__* pServer; } ;
typedef  TYPE_1__ HttpThread ;
typedef  TYPE_2__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_MAX_EVENTS ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 scalar_t__ epoll_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ httpAcceptHttpConnection ; 
 int /*<<< orphan*/  httpError (char*,...) ; 
 scalar_t__ httpProcessHttpData ; 
 int /*<<< orphan*/  httpTrace (char*,...) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

bool httpInitConnect(HttpServer *pServer) {
  int            i;
  pthread_attr_t thattr;
  HttpThread *   pThread;

  pServer->pThreads = (HttpThread *)malloc(sizeof(HttpThread) * (size_t)pServer->numOfThreads);
  if (pServer->pThreads == NULL) {
    httpError("init error no enough memory");
    return false;
  }
  memset(pServer->pThreads, 0, sizeof(HttpThread) * (size_t)pServer->numOfThreads);

  pthread_attr_init(&thattr);
  pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_JOINABLE);
  pThread = pServer->pThreads;
  for (i = 0; i < pServer->numOfThreads; ++i) {
    sprintf(pThread->label, "%s%d", pServer->label, i);
    pThread->pServer = pServer;
    pThread->processData = pServer->processData;
    pThread->threadId = i;

    if (pthread_mutex_init(&(pThread->threadMutex), NULL) < 0) {
      httpError("http thread:%s, failed to init HTTP process data mutex, reason:%s", pThread->label, strerror(errno));
      return false;
    }

    if (pthread_cond_init(&(pThread->fdReady), NULL) != 0) {
      httpError("http thread:%s, init HTTP condition variable failed, reason:%s", pThread->label, strerror(errno));
      return false;
    }

    pThread->pollFd = epoll_create(HTTP_MAX_EVENTS);  // size does not matter
    if (pThread->pollFd < 0) {
      httpError("http thread:%s, failed to create HTTP epoll", pThread->label);
      return false;
    }

    if (pthread_create(&(pThread->thread), &thattr, (void *)httpProcessHttpData, (void *)(pThread)) != 0) {
      httpError("http thread:%s, failed to create HTTP process data thread, reason:%s",
                pThread->label, strerror(errno));
      return false;
    }

    httpTrace("http thread:%p:%s, initialized", pThread, pThread->label);
    pThread++;
  }

  if (pthread_create(&(pServer->thread), &thattr, (void *)httpAcceptHttpConnection, (void *)(pServer)) != 0) {
    httpError("http server:%s, failed to create Http accept thread, reason:%s", pServer->label, strerror(errno));
    return false;
  }

  pthread_attr_destroy(&thattr);

  httpTrace("http server:%s, initialized, ip:%s:%u, numOfThreads:%d", pServer->label, pServer->serverIp,
            pServer->serverPort, pServer->numOfThreads);
  return true;
}