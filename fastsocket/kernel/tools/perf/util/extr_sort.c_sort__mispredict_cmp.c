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
struct hist_entry {TYPE_2__* branch_info; } ;
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ mispred; scalar_t__ predicted; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;

/* Variables and functions */

__attribute__((used)) static int64_t
sort__mispredict_cmp(struct hist_entry *left, struct hist_entry *right)
{
	const unsigned char mp = left->branch_info->flags.mispred !=
					right->branch_info->flags.mispred;
	const unsigned char p = left->branch_info->flags.predicted !=
					right->branch_info->flags.predicted;

	return mp || p;
}