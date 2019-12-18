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
struct hist_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  COMPUTE_DELTA 130 
#define  COMPUTE_RATIO 129 
#define  COMPUTE_WEIGHTED_DIFF 128 
 int compute ; 
 int formula_delta (struct hist_entry*,char*,size_t) ; 
 int formula_ratio (struct hist_entry*,char*,size_t) ; 
 int formula_wdiff (struct hist_entry*,char*,size_t) ; 

int perf_diff__formula(char *buf, size_t size, struct hist_entry *he)
{
	switch (compute) {
	case COMPUTE_DELTA:
		return formula_delta(he, buf, size);
	case COMPUTE_RATIO:
		return formula_ratio(he, buf, size);
	case COMPUTE_WEIGHTED_DIFF:
		return formula_wdiff(he, buf, size);
	default:
		BUG_ON(1);
	}

	return -1;
}