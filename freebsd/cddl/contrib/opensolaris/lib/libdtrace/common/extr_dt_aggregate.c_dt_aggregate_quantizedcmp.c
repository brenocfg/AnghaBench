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
typedef  int uint_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ DTRACE_QUANTIZE_BUCKETVAL (int) ; 
 int DTRACE_QUANTIZE_NBUCKETS ; 
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 

__attribute__((used)) static int
dt_aggregate_quantizedcmp(int64_t *lhs, int64_t *rhs)
{
	int nbuckets = DTRACE_QUANTIZE_NBUCKETS;
	long double ltotal = 0, rtotal = 0;
	int64_t lzero, rzero;
	uint_t i;

	for (i = 0; i < nbuckets; i++) {
		int64_t bucketval = DTRACE_QUANTIZE_BUCKETVAL(i);

		if (bucketval == 0) {
			lzero = lhs[i];
			rzero = rhs[i];
		}

		ltotal += (long double)bucketval * (long double)lhs[i];
		rtotal += (long double)bucketval * (long double)rhs[i];
	}

	if (ltotal < rtotal)
		return (DT_LESSTHAN);

	if (ltotal > rtotal)
		return (DT_GREATERTHAN);

	/*
	 * If they're both equal, then we will compare based on the weights at
	 * zero.  If the weights at zero are equal, then this will be judged a
	 * tie and will be resolved based on the key comparison.
	 */
	if (lzero < rzero)
		return (DT_LESSTHAN);

	if (lzero > rzero)
		return (DT_GREATERTHAN);

	return (0);
}