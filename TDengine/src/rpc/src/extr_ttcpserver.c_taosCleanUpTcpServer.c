#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numOfThreads; int /*<<< orphan*/  label; struct TYPE_4__* pThreadObj; int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  fdReady; int /*<<< orphan*/  thread; int /*<<< orphan*/  pollFd; scalar_t__ pHead; } ;
typedef  TYPE_1__ SThreadObj ;
typedef  TYPE_1__ SServerObj ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCleanUpFdObj (scalar_t__) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

void taosCleanUpTcpServer(void *handle) {
  int         i;
  SThreadObj *pThreadObj;
  SServerObj *pServerObj = (SServerObj *)handle;

  if (pServerObj == NULL) return;

  pthread_cancel(pServerObj->thread);
  pthread_join(pServerObj->thread, NULL);

  for (i = 0; i < pServerObj->numOfThreads; ++i) {
    pThreadObj = pServerObj->pThreadObj + i;

    while (pThreadObj->pHead) {
      taosCleanUpFdObj(pThreadObj->pHead);
      pThreadObj->pHead = pThreadObj->pHead;
    }

    close(pThreadObj->pollFd);
    pthread_cancel(pThreadObj->thread);
    pthread_join(pThreadObj->thread, NULL);
    pthread_cond_destroy(&(pThreadObj->fdReady));
    pthread_mutex_destroy(&(pThreadObj->threadMutex));
  }

  tfree(pServerObj->pThreadObj);
  tTrace("TCP:%s, TCP server is cleaned up", pServerObj->label);

  tfree(pServerObj);
}