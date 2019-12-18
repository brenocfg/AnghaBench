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
struct TYPE_5__ {int queueSize; TYPE_2__* queue; int /*<<< orphan*/  stmMutex; int /*<<< orphan*/  queueMutex; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  emptySem; int /*<<< orphan*/  thread; int /*<<< orphan*/  (* cleanUp ) () ;} ;
typedef  TYPE_1__ module_t ;
struct TYPE_6__ {struct TYPE_6__* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ taosCheckPthreadValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosResetPthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 
 int /*<<< orphan*/  tsem_destroy (int /*<<< orphan*/ *) ; 

void taosCleanUpModule(module_t *pMod) {
  int i;

  if (pMod->cleanUp) pMod->cleanUp();

  if (taosCheckPthreadValid(pMod->thread)) {
    pthread_cancel(pMod->thread);
    pthread_join(pMod->thread, NULL);
  }

  taosResetPthread(&pMod->thread);
  tsem_destroy(&pMod->emptySem);
  tsem_destroy(&pMod->fullSem);
  pthread_mutex_destroy(&pMod->queueMutex);
  pthread_mutex_destroy(&pMod->stmMutex);

  for (i = 0; i < pMod->queueSize; ++i) {
    tfree(pMod->queue[i].msg);
  }

  tfree(pMod->queue);

  memset(pMod, 0, sizeof(module_t));
}