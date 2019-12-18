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
typedef  double u64 ;
struct hist_entry {TYPE_2__* hists; } ;
struct TYPE_3__ {double total_period; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static double get_period_percent(struct hist_entry *he, u64 period)
{
	u64 total = he->hists->stats.total_period;
	return (period * 100.0) / total;
}