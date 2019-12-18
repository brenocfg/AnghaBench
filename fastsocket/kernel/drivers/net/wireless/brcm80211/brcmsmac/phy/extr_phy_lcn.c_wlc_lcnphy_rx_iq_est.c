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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct lcnphy_iq_est {int iq_prod; int i_pwr; int q_pwr; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool
wlc_lcnphy_rx_iq_est(struct brcms_phy *pi,
		     u16 num_samps,
		     u8 wait_time, struct lcnphy_iq_est *iq_est)
{
	int wait_count = 0;
	bool result = true;
	u8 phybw40;
	phybw40 = CHSPEC_IS40(pi->radio_chanspec);

	mod_phy_reg(pi, 0x6da, (0x1 << 5), (1) << 5);

	mod_phy_reg(pi, 0x410, (0x1 << 3), (0) << 3);

	mod_phy_reg(pi, 0x482, (0xffff << 0), (num_samps) << 0);

	mod_phy_reg(pi, 0x481, (0xff << 0), ((u16) wait_time) << 0);

	mod_phy_reg(pi, 0x481, (0x1 << 8), (0) << 8);

	mod_phy_reg(pi, 0x481, (0x1 << 9), (1) << 9);

	while (read_phy_reg(pi, 0x481) & (0x1 << 9)) {

		if (wait_count > (10 * 500)) {
			result = false;
			goto cleanup;
		}
		udelay(100);
		wait_count++;
	}

	iq_est->iq_prod = ((u32) read_phy_reg(pi, 0x483) << 16) |
			  (u32) read_phy_reg(pi, 0x484);
	iq_est->i_pwr = ((u32) read_phy_reg(pi, 0x485) << 16) |
			(u32) read_phy_reg(pi, 0x486);
	iq_est->q_pwr = ((u32) read_phy_reg(pi, 0x487) << 16) |
			(u32) read_phy_reg(pi, 0x488);

cleanup:
	mod_phy_reg(pi, 0x410, (0x1 << 3), (1) << 3);

	mod_phy_reg(pi, 0x6da, (0x1 << 5), (0) << 5);

	return result;
}