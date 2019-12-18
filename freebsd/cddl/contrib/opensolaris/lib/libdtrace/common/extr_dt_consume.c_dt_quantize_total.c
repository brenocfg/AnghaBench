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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 size_t DTRACEOPT_AGGZOOM ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int DTRACE_AGGZOOM_MAX ; 
 long double dt_fabsl (long double) ; 

__attribute__((used)) static void
dt_quantize_total(dtrace_hdl_t *dtp, int64_t datum, long double *total)
{
	long double val = dt_fabsl((long double)datum);

	if (dtp->dt_options[DTRACEOPT_AGGZOOM] == DTRACEOPT_UNSET) {
		*total += val;
		return;
	}

	/*
	 * If we're zooming in on an aggregation, we want the height of the
	 * highest value to be approximately 95% of total bar height -- so we
	 * adjust up by the reciprocal of DTRACE_AGGZOOM_MAX when comparing to
	 * our highest value.
	 */
	val *= 1 / DTRACE_AGGZOOM_MAX;

	if (*total < val)
		*total = val;
}