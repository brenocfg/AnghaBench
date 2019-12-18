#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * customFree; int /*<<< orphan*/ * customAlloc; } ;
typedef  TYPE_1__ ZSTD_customMem ;
struct TYPE_13__ {int allJobsCompleted; int jobIDMask; int /*<<< orphan*/  seqPool; int /*<<< orphan*/  cctxPool; int /*<<< orphan*/  bufPool; int /*<<< orphan*/  jobs; int /*<<< orphan*/  factory; int /*<<< orphan*/  roundBuff; int /*<<< orphan*/  serial; TYPE_1__ cMem; int /*<<< orphan*/  params; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 unsigned int MIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POOL_create_advanced (unsigned int,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTDMT_CCtxParam_setNbWorkers (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ZSTDMT_NBWORKERS_MAX ; 
 int /*<<< orphan*/  ZSTDMT_createBufferPool (unsigned int,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTDMT_createCCtxPool (unsigned int,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTDMT_createJobsTable (int*,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTDMT_createSeqPool (unsigned int,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTDMT_freeCCtx (TYPE_2__*) ; 
 int ZSTDMT_serialState_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_calloc (int,TYPE_1__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kNullRoundBuff ; 

ZSTDMT_CCtx* ZSTDMT_createCCtx_advanced(unsigned nbWorkers, ZSTD_customMem cMem)
{
    ZSTDMT_CCtx* mtctx;
    U32 nbJobs = nbWorkers + 2;
    int initError;
    DEBUGLOG(3, "ZSTDMT_createCCtx_advanced (nbWorkers = %u)", nbWorkers);

    if (nbWorkers < 1) return NULL;
    nbWorkers = MIN(nbWorkers , ZSTDMT_NBWORKERS_MAX);
    if ((cMem.customAlloc!=NULL) ^ (cMem.customFree!=NULL))
        /* invalid custom allocator */
        return NULL;

    mtctx = (ZSTDMT_CCtx*) ZSTD_calloc(sizeof(ZSTDMT_CCtx), cMem);
    if (!mtctx) return NULL;
    ZSTDMT_CCtxParam_setNbWorkers(&mtctx->params, nbWorkers);
    mtctx->cMem = cMem;
    mtctx->allJobsCompleted = 1;
    mtctx->factory = POOL_create_advanced(nbWorkers, 0, cMem);
    mtctx->jobs = ZSTDMT_createJobsTable(&nbJobs, cMem);
    assert(nbJobs > 0); assert((nbJobs & (nbJobs - 1)) == 0);  /* ensure nbJobs is a power of 2 */
    mtctx->jobIDMask = nbJobs - 1;
    mtctx->bufPool = ZSTDMT_createBufferPool(nbWorkers, cMem);
    mtctx->cctxPool = ZSTDMT_createCCtxPool(nbWorkers, cMem);
    mtctx->seqPool = ZSTDMT_createSeqPool(nbWorkers, cMem);
    initError = ZSTDMT_serialState_init(&mtctx->serial);
    mtctx->roundBuff = kNullRoundBuff;
    if (!mtctx->factory | !mtctx->jobs | !mtctx->bufPool | !mtctx->cctxPool | !mtctx->seqPool | initError) {
        ZSTDMT_freeCCtx(mtctx);
        return NULL;
    }
    DEBUGLOG(3, "mt_cctx created, for %u threads", nbWorkers);
    return mtctx;
}