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
typedef  int u32 ;
typedef  int /*<<< orphan*/  temp_offset ;
struct phytbl_info {int* tbl_ptr; int tbl_len; int tbl_width; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_PAPDCOMPDELTATBL ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_clear_papd_comptable(struct brcms_phy *pi)
{
	u32 j;
	struct phytbl_info tab;
	u32 temp_offset[128];
	tab.tbl_ptr = temp_offset;
	tab.tbl_len = 128;
	tab.tbl_id = LCNPHY_TBL_ID_PAPDCOMPDELTATBL;
	tab.tbl_width = 32;
	tab.tbl_offset = 0;

	memset(temp_offset, 0, sizeof(temp_offset));
	for (j = 1; j < 128; j += 2)
		temp_offset[j] = 0x80000;

	wlc_lcnphy_write_table(pi, &tab);
	return;
}