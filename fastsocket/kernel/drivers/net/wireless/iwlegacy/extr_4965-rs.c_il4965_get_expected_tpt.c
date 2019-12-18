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
struct il_scale_tbl_info {int /*<<< orphan*/ * expected_tpt; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static s32
il4965_get_expected_tpt(struct il_scale_tbl_info *tbl, int rs_idx)
{
	if (tbl->expected_tpt)
		return tbl->expected_tpt[rs_idx];
	return 0;
}