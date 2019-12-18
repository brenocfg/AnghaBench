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
typedef  int /*<<< orphan*/  ZSTDv03_Dctx ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 size_t ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 

size_t ZSTDv03_freeDCtx(ZSTDv03_Dctx* dctx)
{
    return ZSTD_freeDCtx((ZSTD_DCtx*)dctx);
}