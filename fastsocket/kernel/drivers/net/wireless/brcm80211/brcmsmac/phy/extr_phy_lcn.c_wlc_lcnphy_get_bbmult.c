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
struct phytbl_info {int* tbl_ptr; int tbl_len; int tbl_offset; int tbl_width; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_IQLOCAL ; 
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static u8 wlc_lcnphy_get_bbmult(struct brcms_phy *pi)
{
	u16 m0m1;
	struct phytbl_info tab;

	tab.tbl_ptr = &m0m1;
	tab.tbl_len = 1;
	tab.tbl_id = LCNPHY_TBL_ID_IQLOCAL;
	tab.tbl_offset = 87;
	tab.tbl_width = 16;
	wlc_lcnphy_read_table(pi, &tab);

	return (u8) ((m0m1 & 0xff00) >> 8);
}