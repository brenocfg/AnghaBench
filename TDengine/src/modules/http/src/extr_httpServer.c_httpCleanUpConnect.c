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
struct TYPE_6__ {int numOfThreads; int /*<<< orphan*/  label; TYPE_1__* pThreads; int /*<<< orphan*/  thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  threadMutex; int /*<<< orphan*/  fdReady; int /*<<< orphan*/  thread; scalar_t__ pHead; int /*<<< orphan*/  pollFd; } ;
typedef  TYPE_1__ HttpThread ;
typedef  TYPE_2__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  httpCleanUpContext (scalar_t__) ; 
 int /*<<< orphan*/  httpTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosCloseSocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

void httpCleanUpConnect(HttpServer *pServer) {
  int         i;
  HttpThread *pThread;

  if (pServer == NULL) return;

  pthread_cancel(pServer->thread);
  pthread_join(pServer->thread, NULL);

  for (i = 0; i < pServer->numOfThreads; ++i) {
    pThread = pServer->pThreads + i;
    taosCloseSocket(pThread->pollFd);

    while (pThread->pHead) {
      httpCleanUpContext(pThread->pHead);
    }

    pthread_cancel(pThread->thread);
    pthread_join(pThread->thread, NULL);
    pthread_cond_destroy(&(pThread->fdReady));
    pthread_mutex_destroy(&(pThread->threadMutex));
  }

  tfree(pServer->pThreads);
  httpTrace("http server:%s is cleaned up", pServer->label);
}