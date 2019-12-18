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
struct gelic_wl_scan_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void update_best(struct gelic_wl_scan_info **best,
			struct gelic_wl_scan_info *candid,
			int *best_weight,
			int *weight)
{
	if (*best_weight < ++(*weight)) {
		*best_weight = *weight;
		*best = candid;
	}
}