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
struct throtl_grp {int* bps; int* iops; } ;

/* Variables and functions */

__attribute__((used)) static bool tg_no_rule_group(struct throtl_grp *tg, bool rw) {
	if (tg->bps[rw] == -1 && tg->iops[rw] == -1)
		return 1;
	return 0;
}