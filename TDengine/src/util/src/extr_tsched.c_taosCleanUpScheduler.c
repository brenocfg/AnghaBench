#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numOfThreads; struct TYPE_5__* qthread; struct TYPE_5__* queue; int /*<<< orphan*/  queueMutex; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  emptySem; } ;
typedef  TYPE_1__ SSchedQueue ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cancel (TYPE_1__) ; 
 int /*<<< orphan*/  pthread_join (TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsem_destroy (int /*<<< orphan*/ *) ; 

void taosCleanUpScheduler(void *param) {
  SSchedQueue *pSched = (SSchedQueue *)param;
  if (pSched == NULL) return;

  for (int i = 0; i < pSched->numOfThreads; ++i) {
    pthread_cancel(pSched->qthread[i]);
  }
  for (int i = 0; i < pSched->numOfThreads; ++i) {
    pthread_join(pSched->qthread[i], NULL);
  }

  tsem_destroy(&pSched->emptySem);
  tsem_destroy(&pSched->fullSem);
  pthread_mutex_destroy(&pSched->queueMutex);

  free(pSched->queue);
  free(pSched->qthread);
  free(pSched); // fix memory leak
}