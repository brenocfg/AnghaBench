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
struct phytbl_info {int dummy; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_phy_read_table (struct brcms_phy*,struct phytbl_info*,int,int,int) ; 

void wlc_lcnphy_read_table(struct brcms_phy *pi, struct phytbl_info *pti)
{
	wlc_phy_read_table(pi, pti, 0x455, 0x457, 0x456);
}