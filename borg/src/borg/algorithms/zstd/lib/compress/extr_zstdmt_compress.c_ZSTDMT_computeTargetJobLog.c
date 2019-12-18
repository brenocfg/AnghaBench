#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ windowLog; scalar_t__ chainLog; } ;
struct TYPE_5__ {scalar_t__ enableLdm; } ;
struct TYPE_7__ {TYPE_2__ cParams; TYPE_1__ ldmParams; } ;
typedef  TYPE_3__ ZSTD_CCtx_params ;

/* Variables and functions */
 int MAX (int,scalar_t__) ; 

__attribute__((used)) static unsigned ZSTDMT_computeTargetJobLog(ZSTD_CCtx_params const params)
{
    if (params.ldmParams.enableLdm)
        /* In Long Range Mode, the windowLog is typically oversized.
         * In which case, it's preferable to determine the jobSize
         * based on chainLog instead. */
        return MAX(21, params.cParams.chainLog + 4);
    return MAX(20, params.cParams.windowLog + 2);
}