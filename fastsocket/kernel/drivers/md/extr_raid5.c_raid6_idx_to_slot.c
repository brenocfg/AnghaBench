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
struct stripe_head {int pd_idx; int qd_idx; scalar_t__ ddf_layout; } ;

/* Variables and functions */

__attribute__((used)) static int raid6_idx_to_slot(int idx, struct stripe_head *sh,
			     int *count, int syndrome_disks)
{
	int slot = *count;

	if (sh->ddf_layout)
		(*count)++;
	if (idx == sh->pd_idx)
		return syndrome_disks;
	if (idx == sh->qd_idx)
		return syndrome_disks + 1;
	if (!sh->ddf_layout)
		(*count)++;
	return slot;
}