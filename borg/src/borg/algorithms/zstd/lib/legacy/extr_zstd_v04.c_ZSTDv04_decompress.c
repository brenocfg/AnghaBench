#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 size_t ZSTDv04_decompressDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTDv04_decompress(void* dst, size_t maxDstSize, const void* src, size_t srcSize)
{
#if defined(ZSTD_HEAPMODE) && (ZSTD_HEAPMODE==1)
    size_t regenSize;
    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    if (dctx==NULL) return ERROR(memory_allocation);
    regenSize = ZSTDv04_decompressDCtx(dctx, dst, maxDstSize, src, srcSize);
    ZSTD_freeDCtx(dctx);
    return regenSize;
#else
    ZSTD_DCtx dctx;
    return ZSTDv04_decompressDCtx(&dctx, dst, maxDstSize, src, srcSize);
#endif
}