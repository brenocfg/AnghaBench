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
struct TYPE_5__ {size_t pos; size_t size; void* dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {size_t pos; size_t size; void const* src; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZBUFF_CCtx ;

/* Variables and functions */
 size_t ZSTD_compressStream (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

size_t ZBUFF_compressContinue(ZBUFF_CCtx* zbc,
                              void* dst, size_t* dstCapacityPtr,
                        const void* src, size_t* srcSizePtr)
{
    size_t result;
    ZSTD_outBuffer outBuff;
    ZSTD_inBuffer inBuff;
    outBuff.dst = dst;
    outBuff.pos = 0;
    outBuff.size = *dstCapacityPtr;
    inBuff.src = src;
    inBuff.pos = 0;
    inBuff.size = *srcSizePtr;
    result = ZSTD_compressStream(zbc, &outBuff, &inBuff);
    *dstCapacityPtr = outBuff.pos;
    *srcSizePtr = inBuff.pos;
    return result;
}