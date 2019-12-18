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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_iq_est {int i_pwr; int q_pwr; int iq_prod; } ;
struct TYPE_2__ {size_t phy_corenum; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 int NPHY_IqestCmd_iqMode ; 
 int NPHY_IqestCmd_iqstart ; 
 int NPHY_IqestIqAccHi (size_t) ; 
 int NPHY_IqestIqAccLo (size_t) ; 
 int NPHY_IqestipwrAccHi (size_t) ; 
 int NPHY_IqestipwrAccLo (size_t) ; 
 int NPHY_IqestqpwrAccHi (size_t) ; 
 int NPHY_IqestqpwrAccLo (size_t) ; 
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

void
wlc_phy_rx_iq_est_nphy(struct brcms_phy *pi, struct phy_iq_est *est,
		       u16 num_samps, u8 wait_time, u8 wait_for_crs)
{
	u8 core;

	write_phy_reg(pi, 0x12b, num_samps);
	mod_phy_reg(pi, 0x12a, (0xff << 0), (wait_time << 0));
	mod_phy_reg(pi, 0x129, NPHY_IqestCmd_iqMode,
		    (wait_for_crs) ? NPHY_IqestCmd_iqMode : 0);

	mod_phy_reg(pi, 0x129, NPHY_IqestCmd_iqstart, NPHY_IqestCmd_iqstart);

	SPINWAIT(((read_phy_reg(pi, 0x129) & NPHY_IqestCmd_iqstart) != 0),
		 10000);
	if (WARN(read_phy_reg(pi, 0x129) & NPHY_IqestCmd_iqstart,
		 "HW error: rxiq est"))
		return;

	if ((read_phy_reg(pi, 0x129) & NPHY_IqestCmd_iqstart) == 0) {
		for (core = 0; core < pi->pubpi.phy_corenum; core++) {
			est[core].i_pwr =
				(read_phy_reg(pi,
					      NPHY_IqestipwrAccHi(core)) << 16)
				| read_phy_reg(pi, NPHY_IqestipwrAccLo(core));
			est[core].q_pwr =
				(read_phy_reg(pi,
					      NPHY_IqestqpwrAccHi(core)) << 16)
				| read_phy_reg(pi, NPHY_IqestqpwrAccLo(core));
			est[core].iq_prod =
				(read_phy_reg(pi,
					      NPHY_IqestIqAccHi(core)) << 16) |
				read_phy_reg(pi, NPHY_IqestIqAccLo(core));
		}
	}
}