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
struct TYPE_4__ {int /*<<< orphan*/  params; } ;
typedef  TYPE_1__ ZSTDMT_CCtx ;

/* Variables and functions */
 size_t ZSTDMT_initCStream_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 

size_t ZSTDMT_resetCStream(ZSTDMT_CCtx* mtctx, unsigned long long pledgedSrcSize)
{
    if (!pledgedSrcSize) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    return ZSTDMT_initCStream_internal(mtctx, NULL, 0, ZSTD_dct_auto, 0, mtctx->params,
                                       pledgedSrcSize);
}