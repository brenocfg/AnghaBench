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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int edcrs_threshold_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_edcrs_lock(struct brcms_phy_pub *pih, bool lock)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	pi->edcrs_threshold_lock = lock;

	write_phy_reg(pi, 0x22c, 0x46b);
	write_phy_reg(pi, 0x22d, 0x46b);
	write_phy_reg(pi, 0x22e, 0x3c0);
	write_phy_reg(pi, 0x22f, 0x3c0);
}