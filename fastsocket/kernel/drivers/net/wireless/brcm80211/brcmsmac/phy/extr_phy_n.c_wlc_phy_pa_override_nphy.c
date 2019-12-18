#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int rfctrlIntc1_save; int rfctrlIntc2_save; int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 void* read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_pa_override_nphy(struct brcms_phy *pi, bool en)
{
	u16 rfctrlintc_override_val;

	if (!en) {

		pi->rfctrlIntc1_save = read_phy_reg(pi, 0x91);
		pi->rfctrlIntc2_save = read_phy_reg(pi, 0x92);

		if (NREV_GE(pi->pubpi.phy_rev, 7))
			rfctrlintc_override_val = 0x1480;
		else if (NREV_GE(pi->pubpi.phy_rev, 3))
			rfctrlintc_override_val =
				CHSPEC_IS5G(pi->radio_chanspec) ? 0x600 : 0x480;
		else
			rfctrlintc_override_val =
				CHSPEC_IS5G(pi->radio_chanspec) ? 0x180 : 0x120;

		write_phy_reg(pi, 0x91, rfctrlintc_override_val);
		write_phy_reg(pi, 0x92, rfctrlintc_override_val);
	} else {
		write_phy_reg(pi, 0x91, pi->rfctrlIntc1_save);
		write_phy_reg(pi, 0x92, pi->rfctrlIntc2_save);
	}

}