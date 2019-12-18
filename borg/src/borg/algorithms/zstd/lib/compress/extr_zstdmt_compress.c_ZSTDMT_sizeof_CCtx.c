#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTDMT_jobDescription ;
struct TYPE_4__ {size_t capacity; } ;
struct TYPE_5__ {int jobIDMask; TYPE_1__ roundBuff; int /*<<< orphan*/  cdictLocal; int /*<<< orphan*/  seqPool; int /*<<< orphan*/  cctxPool; int /*<<< orphan*/  bufPool; int /*<<< orphan*/  factory; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */
 size_t POOL_sizeof (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_sizeof_CCtxPool (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_sizeof_bufferPool (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_sizeof_seqPool (int /*<<< orphan*/ ) ; 
 size_t ZSTD_sizeof_CDict (int /*<<< orphan*/ ) ; 

size_t ZSTDMT_sizeof_CCtx(ZSTDMT_CCtx* mtctx)
{
    if (mtctx == NULL) return 0;   /* supports sizeof NULL */
    return sizeof(*mtctx)
            + POOL_sizeof(mtctx->factory)
            + ZSTDMT_sizeof_bufferPool(mtctx->bufPool)
            + (mtctx->jobIDMask+1) * sizeof(ZSTDMT_jobDescription)
            + ZSTDMT_sizeof_CCtxPool(mtctx->cctxPool)
            + ZSTDMT_sizeof_seqPool(mtctx->seqPool)
            + ZSTD_sizeof_CDict(mtctx->cdictLocal)
            + mtctx->roundBuff.capacity;
}