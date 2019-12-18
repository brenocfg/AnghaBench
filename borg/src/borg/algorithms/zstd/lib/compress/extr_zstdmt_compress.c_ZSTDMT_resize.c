#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  params; int /*<<< orphan*/ * seqPool; int /*<<< orphan*/ * cctxPool; int /*<<< orphan*/ * bufPool; int /*<<< orphan*/  factory; } ;
typedef  TYPE_1__ ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ POOL_resize (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ZSTDMT_CCtxParam_setNbWorkers (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * ZSTDMT_expandBufferPool (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * ZSTDMT_expandCCtxPool (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ZSTDMT_expandJobsTable (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * ZSTDMT_expandSeqPool (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memory_allocation ; 

__attribute__((used)) static size_t ZSTDMT_resize(ZSTDMT_CCtx* mtctx, unsigned nbWorkers)
{
    if (POOL_resize(mtctx->factory, nbWorkers)) return ERROR(memory_allocation);
    CHECK_F( ZSTDMT_expandJobsTable(mtctx, nbWorkers) );
    mtctx->bufPool = ZSTDMT_expandBufferPool(mtctx->bufPool, nbWorkers);
    if (mtctx->bufPool == NULL) return ERROR(memory_allocation);
    mtctx->cctxPool = ZSTDMT_expandCCtxPool(mtctx->cctxPool, nbWorkers);
    if (mtctx->cctxPool == NULL) return ERROR(memory_allocation);
    mtctx->seqPool = ZSTDMT_expandSeqPool(mtctx->seqPool, nbWorkers);
    if (mtctx->seqPool == NULL) return ERROR(memory_allocation);
    ZSTDMT_CCtxParam_setNbWorkers(&mtctx->params, nbWorkers);
    return 0;
}