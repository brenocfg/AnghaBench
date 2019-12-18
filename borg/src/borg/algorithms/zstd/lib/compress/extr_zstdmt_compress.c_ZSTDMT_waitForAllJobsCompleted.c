#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int doneJobID; unsigned int nextJobID; unsigned int jobIDMask; TYPE_2__* jobs; } ;
typedef  TYPE_3__ ZSTDMT_CCtx ;
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ consumed; int /*<<< orphan*/  job_mutex; int /*<<< orphan*/  job_cond; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int /*<<< orphan*/  ZSTD_PTHREAD_MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_waitForAllJobsCompleted(ZSTDMT_CCtx* mtctx)
{
    DEBUGLOG(4, "ZSTDMT_waitForAllJobsCompleted");
    while (mtctx->doneJobID < mtctx->nextJobID) {
        unsigned const jobID = mtctx->doneJobID & mtctx->jobIDMask;
        ZSTD_PTHREAD_MUTEX_LOCK(&mtctx->jobs[jobID].job_mutex);
        while (mtctx->jobs[jobID].consumed < mtctx->jobs[jobID].src.size) {
            DEBUGLOG(4, "waiting for jobCompleted signal from job %u", mtctx->doneJobID);   /* we want to block when waiting for data to flush */
            ZSTD_pthread_cond_wait(&mtctx->jobs[jobID].job_cond, &mtctx->jobs[jobID].job_mutex);
        }
        ZSTD_pthread_mutex_unlock(&mtctx->jobs[jobID].job_mutex);
        mtctx->doneJobID++;
    }
}