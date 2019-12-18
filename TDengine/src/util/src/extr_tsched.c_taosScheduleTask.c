#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t emptySlot; int queueSize; int /*<<< orphan*/  label; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  queueMutex; int /*<<< orphan*/ * queue; int /*<<< orphan*/  emptySem; } ;
typedef  TYPE_1__ SSchedQueue ;
typedef  int /*<<< orphan*/  SSchedMsg ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pTrace (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ tsem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ tsem_wait (int /*<<< orphan*/ *) ; 

int taosScheduleTask(void *qhandle, SSchedMsg *pMsg) {
  SSchedQueue *pSched = (SSchedQueue *)qhandle;
  if (pSched == NULL) {
    pError("sched is not ready, msg:%p is dropped", pMsg);
    return 0;
  }

  while (tsem_wait(&pSched->emptySem) != 0) {
    if (errno != EINTR) {
      pError("wait %s emptySem failed, reason:%s", pSched->label, strerror(errno));
      break;
    }
    pTrace("wait %s emptySem was interrupted", pSched->label);
  }

  if (pthread_mutex_lock(&pSched->queueMutex) != 0)
    pError("lock %s queueMutex failed, reason:%s", pSched->label, strerror(errno));

  pSched->queue[pSched->emptySlot] = *pMsg;
  pSched->emptySlot = (pSched->emptySlot + 1) % pSched->queueSize;

  if (pthread_mutex_unlock(&pSched->queueMutex) != 0)
    pError("unlock %s queueMutex failed, reason:%s", pSched->label, strerror(errno));

  if (tsem_post(&pSched->fullSem) != 0) pError("post %s fullSem failed, reason:%s", pSched->label, strerror(errno));

  return 0;
}