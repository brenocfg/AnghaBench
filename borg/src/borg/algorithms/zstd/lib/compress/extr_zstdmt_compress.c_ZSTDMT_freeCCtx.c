#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  cMem; TYPE_1__ roundBuff; int /*<<< orphan*/  cdictLocal; int /*<<< orphan*/  serial; int /*<<< orphan*/  seqPool; int /*<<< orphan*/  cctxPool; int /*<<< orphan*/  bufPool; scalar_t__ jobIDMask; int /*<<< orphan*/  jobs; int /*<<< orphan*/  factory; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  POOL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_freeBufferPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_freeCCtxPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_freeJobsTable (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_freeSeqPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_releaseAllJobResources (TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTDMT_serialState_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ ) ; 

size_t ZSTDMT_freeCCtx(ZSTDMT_CCtx* mtctx)
{
    if (mtctx==NULL) return 0;   /* compatible with free on NULL */
    POOL_free(mtctx->factory);   /* stop and free worker threads */
    ZSTDMT_releaseAllJobResources(mtctx);  /* release job resources into pools first */
    ZSTDMT_freeJobsTable(mtctx->jobs, mtctx->jobIDMask+1, mtctx->cMem);
    ZSTDMT_freeBufferPool(mtctx->bufPool);
    ZSTDMT_freeCCtxPool(mtctx->cctxPool);
    ZSTDMT_freeSeqPool(mtctx->seqPool);
    ZSTDMT_serialState_free(&mtctx->serial);
    ZSTD_freeCDict(mtctx->cdictLocal);
    if (mtctx->roundBuff.buffer)
        ZSTD_free(mtctx->roundBuff.buffer, mtctx->cMem);
    ZSTD_free(mtctx, mtctx->cMem);
    return 0;
}