#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_5__ {short port; int numOfThreads; int /*<<< orphan*/  thread; TYPE_1__* pThreadObj; int /*<<< orphan*/  label; int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {scalar_t__ pollFd; int threadId; int /*<<< orphan*/  thread; int /*<<< orphan*/  fdReady; int /*<<< orphan*/  threadMutex; void* shandle; int /*<<< orphan*/  label; void* processData; } ;
typedef  TYPE_1__ SThreadObj ;
typedef  TYPE_2__ SServerObj ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 scalar_t__ epoll_create (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tError (char*,char*,...) ; 
 int /*<<< orphan*/  tTrace (char*,char*,char*,short,int) ; 
 scalar_t__ taosAcceptTcpConnection ; 
 scalar_t__ taosProcessTcpData ; 

void *taosInitTcpServer(char *ip, short port, char *label, int numOfThreads, void *fp, void *shandle) {
  int            i;
  SServerObj *   pServerObj;
  pthread_attr_t thattr;
  SThreadObj *   pThreadObj;

  pServerObj = (SServerObj *)malloc(sizeof(SServerObj));
  strcpy(pServerObj->ip, ip);
  pServerObj->port = port;
  strcpy(pServerObj->label, label);
  pServerObj->numOfThreads = numOfThreads;

  pServerObj->pThreadObj = (SThreadObj *)malloc(sizeof(SThreadObj) * (size_t)numOfThreads);
  if (pServerObj->pThreadObj == NULL) {
    tError("TCP:%s no enough memory", label);
    return NULL;
  }
  memset(pServerObj->pThreadObj, 0, sizeof(SThreadObj) * (size_t)numOfThreads);

  pThreadObj = pServerObj->pThreadObj;
  for (i = 0; i < numOfThreads; ++i) {
    pThreadObj->processData = fp;
    strcpy(pThreadObj->label, label);
    pThreadObj->shandle = shandle;

    if (pthread_mutex_init(&(pThreadObj->threadMutex), NULL) < 0) {
      tError("%s failed to init TCP process data mutex, reason:%s", label, strerror(errno));
      return NULL;
    }

    if (pthread_cond_init(&(pThreadObj->fdReady), NULL) != 0) {
      tError("%s init TCP condition variable failed, reason:%s\n", label, strerror(errno));
      return NULL;
    }

    pThreadObj->pollFd = epoll_create(10);  // size does not matter
    if (pThreadObj->pollFd < 0) {
      tError("%s failed to create TCP epoll", label);
      return NULL;
    }

    pthread_attr_init(&thattr);
    pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_JOINABLE);
    if (pthread_create(&(pThreadObj->thread), &thattr, (void *)taosProcessTcpData, (void *)(pThreadObj)) != 0) {
      tError("%s failed to create TCP process data thread, reason:%s", label, strerror(errno));
      return NULL;
    }

    pThreadObj->threadId = i;
    pThreadObj++;
  }

  pthread_attr_init(&thattr);
  pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_JOINABLE);
  if (pthread_create(&(pServerObj->thread), &thattr, (void *)taosAcceptTcpConnection, (void *)(pServerObj)) != 0) {
    tError("%s failed to create TCP accept thread, reason:%s", label, strerror(errno));
    return NULL;
  }

  /*
    if ( pthread_create(&(pServerObj->thread), &thattr,
    (void*)taosAcceptUDConnection, (void *)(pServerObj)) != 0 ) {
      tError("%s failed to create UD accept thread, reason:%s", label,
    strerror(errno));
      return NULL;
    }
  */
  pthread_attr_destroy(&thattr);
  tTrace("%s TCP server is initialized, ip:%s port:%u numOfThreads:%d", label, ip, port, numOfThreads);

  return (void *)pServerObj;
}