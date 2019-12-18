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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 
 long double dt_aggregate_llquantizedsum (scalar_t__*) ; 

__attribute__((used)) static int
dt_aggregate_llquantizedcmp(int64_t *lhs, int64_t *rhs)
{
	long double lsum = dt_aggregate_llquantizedsum(lhs);
	long double rsum = dt_aggregate_llquantizedsum(rhs);
	int64_t lzero, rzero;

	if (lsum < rsum)
		return (DT_LESSTHAN);

	if (lsum > rsum)
		return (DT_GREATERTHAN);

	/*
	 * If they're both equal, then we will compare based on the weights at
	 * zero.  If the weights at zero are equal, then this will be judged a
	 * tie and will be resolved based on the key comparison.
	 */
	lzero = lhs[1];
	rzero = rhs[1];

	if (lzero < rzero)
		return (DT_LESSTHAN);

	if (lzero > rzero)
		return (DT_GREATERTHAN);

	return (0);
}