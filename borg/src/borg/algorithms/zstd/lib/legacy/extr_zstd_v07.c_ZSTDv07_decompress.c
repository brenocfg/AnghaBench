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
typedef  int /*<<< orphan*/  ZSTDv07_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTDv07_createDCtx () ; 
 size_t ZSTDv07_decompressDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTDv07_freeDCtx (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTDv07_decompress(void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
#if defined(ZSTDv07_HEAPMODE) && (ZSTDv07_HEAPMODE==1)
    size_t regenSize;
    ZSTDv07_DCtx* const dctx = ZSTDv07_createDCtx();
    if (dctx==NULL) return ERROR(memory_allocation);
    regenSize = ZSTDv07_decompressDCtx(dctx, dst, dstCapacity, src, srcSize);
    ZSTDv07_freeDCtx(dctx);
    return regenSize;
#else   /* stack mode */
    ZSTDv07_DCtx dctx;
    return ZSTDv07_decompressDCtx(&dctx, dst, dstCapacity, src, srcSize);
#endif
}