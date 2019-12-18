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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct antsel_info {scalar_t__ antsel_type; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 int /*<<< orphan*/ * mimo_2x3_div_antselid_tbl ; 
 int /*<<< orphan*/ * mimo_2x4_div_antselid_tbl ; 

u8 brcms_c_antsel_antsel2id(struct antsel_info *asi, u16 antsel)
{
	u8 antselid = 0;

	if (asi->antsel_type == ANTSEL_2x4) {
		/* 2x4 antenna diversity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antselid = mimo_2x4_div_antselid_tbl[(antsel & 0xf)];
		return antselid;

	} else if (asi->antsel_type == ANTSEL_2x3) {
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		antselid = mimo_2x3_div_antselid_tbl[(antsel & 0xf)];
		return antselid;
	}

	return antselid;
}