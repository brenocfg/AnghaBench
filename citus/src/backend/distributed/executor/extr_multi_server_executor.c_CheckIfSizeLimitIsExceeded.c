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
typedef  long uint64 ;
struct TYPE_3__ {long totalIntermediateResultSize; } ;
typedef  TYPE_1__ DistributedExecutionStats ;

/* Variables and functions */
 long MaxIntermediateResult ; 
 int /*<<< orphan*/  SubPlanLevel ; 

bool
CheckIfSizeLimitIsExceeded(DistributedExecutionStats *executionStats)
{
	uint64 maxIntermediateResultInBytes = 0;

	if (!SubPlanLevel || MaxIntermediateResult < 0)
	{
		return false;
	}

	maxIntermediateResultInBytes = MaxIntermediateResult * 1024L;
	if (executionStats->totalIntermediateResultSize < maxIntermediateResultInBytes)
	{
		return false;
	}

	return true;
}