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
struct TYPE_6__ {int /*<<< orphan*/  thandle; int /*<<< orphan*/  ahandle; int /*<<< orphan*/  (* tfp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fp ) (TYPE_2__*) ;} ;
struct TYPE_5__ {size_t fullSlot; int queueSize; int /*<<< orphan*/  label; int /*<<< orphan*/  emptySem; int /*<<< orphan*/  queueMutex; TYPE_2__* queue; int /*<<< orphan*/  fullSem; } ;
typedef  TYPE_1__ SSchedQueue ;
typedef  TYPE_2__ SSchedMsg ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  pTrace (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tsem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ tsem_wait (int /*<<< orphan*/ *) ; 

void *taosProcessSchedQueue(void *param) {
  SSchedMsg    msg;
  SSchedQueue *pSched = (SSchedQueue *)param;

  while (1) {
    if (tsem_wait(&pSched->fullSem) != 0) {
      if (errno == EINTR) {
        /* sem_wait is interrupted by interrupt, ignore and continue */
        pTrace("wait %s fullSem was interrupted", pSched->label);
        continue;
      }
      pError("wait %s fullSem failed, errno:%d, reason:%s", pSched->label, errno, strerror(errno));
    }

    if (pthread_mutex_lock(&pSched->queueMutex) != 0)
      pError("lock %s queueMutex failed, reason:%s", pSched->label, strerror(errno));

    msg = pSched->queue[pSched->fullSlot];
    memset(pSched->queue + pSched->fullSlot, 0, sizeof(SSchedMsg));
    pSched->fullSlot = (pSched->fullSlot + 1) % pSched->queueSize;

    if (pthread_mutex_unlock(&pSched->queueMutex) != 0)
      pError("unlock %s queueMutex failed, reason:%s\n", pSched->label, strerror(errno));

    if (tsem_post(&pSched->emptySem) != 0)
      pError("post %s emptySem failed, reason:%s\n", pSched->label, strerror(errno));

    if (msg.fp)
      (*(msg.fp))(&msg);
    else if (msg.tfp)
      (*(msg.tfp))(msg.ahandle, msg.thandle);
  }
}