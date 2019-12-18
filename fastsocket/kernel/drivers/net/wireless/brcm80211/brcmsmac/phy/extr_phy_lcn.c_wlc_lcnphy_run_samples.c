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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_2064_REG112 ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  or_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_pu (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_lcnphy_run_samples(struct brcms_phy *pi,
		       u16 num_samps,
		       u16 num_loops, u16 wait, bool iqcalmode)
{

	or_phy_reg(pi, 0x6da, 0x8080);

	mod_phy_reg(pi, 0x642, (0x7f << 0), (num_samps - 1) << 0);
	if (num_loops != 0xffff)
		num_loops--;
	mod_phy_reg(pi, 0x640, (0xffff << 0), num_loops << 0);

	mod_phy_reg(pi, 0x641, (0xffff << 0), wait << 0);

	if (iqcalmode) {

		and_phy_reg(pi, 0x453, (u16) ~(0x1 << 15));
		or_phy_reg(pi, 0x453, (0x1 << 15));
	} else {
		write_phy_reg(pi, 0x63f, 1);
		wlc_lcnphy_tx_pu(pi, 1);
	}

	or_radio_reg(pi, RADIO_2064_REG112, 0x6);
}