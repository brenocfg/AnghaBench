#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int nbWorkers; scalar_t__ jobSize; int /*<<< orphan*/  overlapLog; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;

/* Variables and functions */
 unsigned int ZSTDMT_NBWORKERS_MAX ; 
 int /*<<< orphan*/  ZSTDMT_OVERLAPLOG_DEFAULT ; 

size_t ZSTDMT_CCtxParam_setNbWorkers(ZSTD_CCtx_params* params, unsigned nbWorkers)
{
    if (nbWorkers > ZSTDMT_NBWORKERS_MAX) nbWorkers = ZSTDMT_NBWORKERS_MAX;
    params->nbWorkers = nbWorkers;
    params->overlapLog = ZSTDMT_OVERLAPLOG_DEFAULT;
    params->jobSize = 0;
    return nbWorkers;
}