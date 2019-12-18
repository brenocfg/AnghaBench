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
typedef  size_t u32 ;
typedef  int u16 ;
struct lcnphy_radio_regs {int address; scalar_t__ init_g; scalar_t__ do_init_g; scalar_t__ init_a; scalar_t__ do_init_a; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int RADIO_2064_REG010 ; 
 int RADIO_2064_REG01D ; 
 int RADIO_2064_REG01E ; 
 int RADIO_2064_REG032 ; 
 int RADIO_2064_REG033 ; 
 int RADIO_2064_REG060 ; 
 int RADIO_2064_REG061 ; 
 int RADIO_2064_REG062 ; 
 int RADIO_2064_REG090 ; 
 int RADIO_DEFAULT_CORE ; 
 struct lcnphy_radio_regs* lcnphy_radio_regs_2064 ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_rc_cal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_rcal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_locc (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_radio_2064_init(struct brcms_phy *pi)
{
	u32 i;
	const struct lcnphy_radio_regs *lcnphyregs = NULL;

	lcnphyregs = lcnphy_radio_regs_2064;

	for (i = 0; lcnphyregs[i].address != 0xffff; i++)
		if (CHSPEC_IS5G(pi->radio_chanspec) && lcnphyregs[i].do_init_a)
			write_radio_reg(pi,
					((lcnphyregs[i].address & 0x3fff) |
					 RADIO_DEFAULT_CORE),
					(u16) lcnphyregs[i].init_a);
		else if (lcnphyregs[i].do_init_g)
			write_radio_reg(pi,
					((lcnphyregs[i].address & 0x3fff) |
					 RADIO_DEFAULT_CORE),
					(u16) lcnphyregs[i].init_g);

	write_radio_reg(pi, RADIO_2064_REG032, 0x62);
	write_radio_reg(pi, RADIO_2064_REG033, 0x19);

	write_radio_reg(pi, RADIO_2064_REG090, 0x10);

	write_radio_reg(pi, RADIO_2064_REG010, 0x00);

	if (LCNREV_IS(pi->pubpi.phy_rev, 1)) {

		write_radio_reg(pi, RADIO_2064_REG060, 0x7f);
		write_radio_reg(pi, RADIO_2064_REG061, 0x72);
		write_radio_reg(pi, RADIO_2064_REG062, 0x7f);
	}

	write_radio_reg(pi, RADIO_2064_REG01D, 0x02);
	write_radio_reg(pi, RADIO_2064_REG01E, 0x06);

	mod_phy_reg(pi, 0x4ea, (0x7 << 0), 0 << 0);

	mod_phy_reg(pi, 0x4ea, (0x7 << 3), 1 << 3);

	mod_phy_reg(pi, 0x4ea, (0x7 << 6), 2 << 6);

	mod_phy_reg(pi, 0x4ea, (0x7 << 9), 3 << 9);

	mod_phy_reg(pi, 0x4ea, (0x7 << 12), 4 << 12);

	write_phy_reg(pi, 0x4ea, 0x4688);

	mod_phy_reg(pi, 0x4eb, (0x7 << 0), 2 << 0);

	mod_phy_reg(pi, 0x4eb, (0x7 << 6), 0 << 6);

	mod_phy_reg(pi, 0x46a, (0xffff << 0), 25 << 0);

	wlc_lcnphy_set_tx_locc(pi, 0);

	wlc_lcnphy_rcal(pi);

	wlc_lcnphy_rc_cal(pi);
}