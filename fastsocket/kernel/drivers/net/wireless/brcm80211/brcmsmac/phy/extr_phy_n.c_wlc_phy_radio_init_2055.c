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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_DEFAULT_CORE ; 
 int /*<<< orphan*/  regs_2055 ; 
 int /*<<< orphan*/  wlc_phy_init_radio_regs (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_radio_init_2055(struct brcms_phy *pi)
{
	wlc_phy_init_radio_regs(pi, regs_2055, RADIO_DEFAULT_CORE);
}