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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 
 scalar_t__ dt_stddev (scalar_t__*,int) ; 

__attribute__((used)) static int
dt_aggregate_stddevcmp(int64_t *lhs, int64_t *rhs)
{
	uint64_t lsd = dt_stddev((uint64_t *)lhs, 1);
	uint64_t rsd = dt_stddev((uint64_t *)rhs, 1);

	if (lsd < rsd)
		return (DT_LESSTHAN);

	if (lsd > rsd)
		return (DT_GREATERTHAN);

	return (0);
}