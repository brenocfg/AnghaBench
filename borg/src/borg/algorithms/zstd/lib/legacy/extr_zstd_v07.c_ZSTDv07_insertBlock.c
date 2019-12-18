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
struct TYPE_4__ {char const* previousDstEnd; } ;
typedef  TYPE_1__ ZSTDv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv07_checkContinuity (TYPE_1__*,void const*) ; 

size_t ZSTDv07_insertBlock(ZSTDv07_DCtx* dctx, const void* blockStart, size_t blockSize)
{
    ZSTDv07_checkContinuity(dctx, blockStart);
    dctx->previousDstEnd = (const char*)blockStart + blockSize;
    return blockSize;
}