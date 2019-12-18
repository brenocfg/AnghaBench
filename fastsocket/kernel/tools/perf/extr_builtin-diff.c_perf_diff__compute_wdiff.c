#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int computed; int wdiff; } ;
struct TYPE_3__ {int period; } ;
struct hist_entry {TYPE_2__ diff; TYPE_1__ stat; } ;
typedef  int s64 ;

/* Variables and functions */
 int compute_wdiff_w1 ; 
 int compute_wdiff_w2 ; 
 struct hist_entry* hist_entry__next_pair (struct hist_entry*) ; 

s64 perf_diff__compute_wdiff(struct hist_entry *he)
{
	struct hist_entry *pair = hist_entry__next_pair(he);
	u64 new_period = he->stat.period;
	u64 old_period = pair ? pair->stat.period : 0;

	he->diff.computed = true;

	if (!pair)
		he->diff.wdiff = 0;
	else
		he->diff.wdiff = new_period * compute_wdiff_w2 -
				 old_period * compute_wdiff_w1;

	return he->diff.wdiff;
}