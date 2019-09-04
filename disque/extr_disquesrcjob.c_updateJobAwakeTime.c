#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int mstime_t ;
struct TYPE_7__ {scalar_t__ state; int qtime; int flags; int awakeme; scalar_t__ etime; } ;
typedef  TYPE_1__ job ;
struct TYPE_8__ {int /*<<< orphan*/  awakeme; } ;

/* Variables and functions */
 int JOB_FLAG_BCAST_WILLQUEUE ; 
 scalar_t__ JOB_STATE_ACKED ; 
 scalar_t__ JOB_STATE_ACTIVE ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 scalar_t__ JOB_WILLQUEUE_ADVANCE ; 
 int getNextGCRetryTime (TYPE_1__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skiplistDelete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  skiplistInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 

void updateJobAwakeTime(job *j, mstime_t at) {
    if (at == 0) {
        /* Best case is to handle it for eviction. One second more is added
         * in order to make sure when the job is processed we found it to
         * be already expired. */
        at = (mstime_t)j->etime*1000+1000;

        if (j->state == JOB_STATE_ACKED) {
            /* Try to garbage collect this ACKed job again in the future. */
            mstime_t retry_gc_again = getNextGCRetryTime(j);
            if (retry_gc_again < at) at = retry_gc_again;
        } else if ((j->state == JOB_STATE_ACTIVE ||
                    j->state == JOB_STATE_QUEUED) && j->qtime) {
            /* Schedule the job to be queued, and if the job is flagged
             * BCAST_WILLQUEUE, make sure to awake the job a bit earlier
             * to broadcast a WILLQUEUE message. */
            mstime_t qtime = j->qtime;
            if (j->flags & JOB_FLAG_BCAST_WILLQUEUE)
                qtime -= JOB_WILLQUEUE_ADVANCE;
            if (qtime < at) at = qtime;
        }
    }

    /* Only update the job position into the skiplist if needed. */
    if (at != j->awakeme) {
        /* Remove from skip list. */
        if (j->awakeme) {
            serverAssert(skiplistDelete(server.awakeme,j));
        }
        /* Insert it back again in the skip list with the new awake time. */
        j->awakeme = at;
        skiplistInsert(server.awakeme,j);
    }
}