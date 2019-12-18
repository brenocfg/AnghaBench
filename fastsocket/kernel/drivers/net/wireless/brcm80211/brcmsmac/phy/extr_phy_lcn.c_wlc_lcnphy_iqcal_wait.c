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
typedef  int uint ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wlc_lcnphy_iqcal_active (struct brcms_phy*) ; 

__attribute__((used)) static bool wlc_lcnphy_iqcal_wait(struct brcms_phy *pi)
{
	uint delay_count = 0;

	while (wlc_lcnphy_iqcal_active(pi)) {
		udelay(100);
		delay_count++;

		if (delay_count > (10 * 500))
			break;
	}

	return (0 == wlc_lcnphy_iqcal_active(pi));
}