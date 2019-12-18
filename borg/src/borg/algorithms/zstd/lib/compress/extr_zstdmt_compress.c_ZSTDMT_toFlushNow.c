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
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_6__ {size_t cSize; size_t dstFlushed; scalar_t__ consumed; int /*<<< orphan*/  job_mutex; TYPE_1__ src; } ;
typedef  TYPE_2__ ZSTDMT_jobDescription ;
struct TYPE_7__ {unsigned int doneJobID; unsigned int const nextJobID; unsigned int const jobIDMask; TYPE_2__* jobs; } ;
typedef  TYPE_3__ ZSTDMT_CCtx ;

/* Variables and functions */
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

size_t ZSTDMT_toFlushNow(ZSTDMT_CCtx* mtctx)
{
    size_t toFlush;
    unsigned const jobID = mtctx->doneJobID;
    assert(jobID <= mtctx->nextJobID);
    if (jobID == mtctx->nextJobID) return 0;   /* no active job => nothing to flush */

    /* look into oldest non-fully-flushed job */
    {   unsigned const wJobID = jobID & mtctx->jobIDMask;
        ZSTDMT_jobDescription* const jobPtr = &mtctx->jobs[wJobID];
        ZSTD_pthread_mutex_lock(&jobPtr->job_mutex);
        {   size_t const cResult = jobPtr->cSize;
            size_t const produced = ZSTD_isError(cResult) ? 0 : cResult;
            size_t const flushed = ZSTD_isError(cResult) ? 0 : jobPtr->dstFlushed;
            assert(flushed <= produced);
            toFlush = produced - flushed;
            if (toFlush==0 && (jobPtr->consumed >= jobPtr->src.size)) {
                /* doneJobID is not-fully-flushed, but toFlush==0 : doneJobID should be compressing some more data */
                assert(jobPtr->consumed < jobPtr->src.size);
            }
        }
        ZSTD_pthread_mutex_unlock(&mtctx->jobs[wJobID].job_mutex);
    }

    return toFlush;
}