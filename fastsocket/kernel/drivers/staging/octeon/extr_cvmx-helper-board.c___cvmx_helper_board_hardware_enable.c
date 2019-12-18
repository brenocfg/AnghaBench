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
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_RX_CLK_SETX (int,int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_CLK_SETX (int,int) ; 
 scalar_t__ CVMX_BOARD_TYPE_CN3005_EVB_HS5 ; 
 scalar_t__ CVMX_BOARD_TYPE_CN3010_EVB_HS5 ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int cvmx_helper_board_get_mii_address (int /*<<< orphan*/ ) ; 
 int cvmx_mdio_read (int,int,int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int __cvmx_helper_board_hardware_enable(int interface)
{
	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_CN3005_EVB_HS5) {
		if (interface == 0) {
			/* Different config for switch port */
			cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(1, interface), 0);
			cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(1, interface), 0);
			/*
			 * Boards with gigabit WAN ports need a
			 * different setting that is compatible with
			 * 100 Mbit settings
			 */
			cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(0, interface),
				       0xc);
			cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(0, interface),
				       0xc);
		}
	} else if (cvmx_sysinfo_get()->board_type ==
		   CVMX_BOARD_TYPE_CN3010_EVB_HS5) {
		/*
		 * Broadcom PHYs require differnet ASX
		 * clocks. Unfortunately many boards don't define a
		 * new board Id and simply mangle the
		 * CN3010_EVB_HS5
		 */
		if (interface == 0) {
			/*
			 * Some boards use a hacked up bootloader that
			 * identifies them as CN3010_EVB_HS5
			 * evaluation boards.  This leads to all kinds
			 * of configuration problems.  Detect one
			 * case, and print warning, while trying to do
			 * the right thing.
			 */
			int phy_addr = cvmx_helper_board_get_mii_address(0);
			if (phy_addr != -1) {
				int phy_identifier =
				    cvmx_mdio_read(phy_addr >> 8,
						   phy_addr & 0xff, 0x2);
				/* Is it a Broadcom PHY? */
				if (phy_identifier == 0x0143) {
					cvmx_dprintf("\n");
					cvmx_dprintf("ERROR:\n");
					cvmx_dprintf
					    ("ERROR: Board type is CVMX_BOARD_TYPE_CN3010_EVB_HS5, but Broadcom PHY found.\n");
					cvmx_dprintf
					    ("ERROR: The board type is mis-configured, and software malfunctions are likely.\n");
					cvmx_dprintf
					    ("ERROR: All boards require a unique board type to identify them.\n");
					cvmx_dprintf("ERROR:\n");
					cvmx_dprintf("\n");
					cvmx_wait(1000000000);
					cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX
						       (0, interface), 5);
					cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX
						       (0, interface), 5);
				}
			}
		}
	}
	return 0;
}