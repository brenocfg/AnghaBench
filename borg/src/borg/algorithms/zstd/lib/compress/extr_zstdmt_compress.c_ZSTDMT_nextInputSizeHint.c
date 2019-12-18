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
struct TYPE_4__ {size_t filled; } ;
struct TYPE_5__ {size_t targetSectionSize; TYPE_1__ inBuff; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */

size_t ZSTDMT_nextInputSizeHint(const ZSTDMT_CCtx* mtctx)
{
    size_t hintInSize = mtctx->targetSectionSize - mtctx->inBuff.filled;
    if (hintInSize==0) hintInSize = mtctx->targetSectionSize;
    return hintInSize;
}