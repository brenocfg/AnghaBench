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
typedef  int u8 ;
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF ; 
 int MDIO_PMA_REG_8727_TWO_WIRE_DATA_MASK ; 
 int MDIO_PMA_REG_8727_TWO_WIRE_SLAVE_ADDR ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_BYTE_CNT ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_CTRL ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_MEM_ADDR ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE ; 
 int MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IDLE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int SFP_EEPROM_PAGE_SIZE ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_8727_read_sfp_module_eeprom(struct bnx2x_phy *phy,
					     struct link_params *params,
					     u8 dev_addr, u16 addr, u8 byte_cnt,
					     u8 *o_buf, u8 is_init)
{
	struct bnx2x *bp = params->bp;
	u16 val, i;

	if (byte_cnt > SFP_EEPROM_PAGE_SIZE) {
		DP(NETIF_MSG_LINK,
		   "Reading from eeprom is limited to 0xf\n");
		return -EINVAL;
	}

	/* Set 2-wire transfer rate of SFP+ module EEPROM
	 * to 100Khz since some DACs(direct attached cables) do
	 * not work at 400Khz.
	 */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_TWO_WIRE_SLAVE_ADDR,
			 ((dev_addr << 8) | 1));

	/* Need to read from 1.8000 to clear it */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_SFP_TWO_WIRE_CTRL,
			&val);

	/* Set the read command byte count */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_BYTE_CNT,
			 ((byte_cnt < 2) ? 2 : byte_cnt));

	/* Set the read command address */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_MEM_ADDR,
			 addr);
	/* Set the destination address */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 0x8004,
			 MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF);

	/* Activate read command */
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_CTRL,
			 0x8002);
	/* Wait appropriate time for two-wire command to finish before
	 * polling the status register
	 */
	usleep_range(1000, 2000);

	/* Wait up to 500us for command complete status */
	for (i = 0; i < 100; i++) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		if ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE)
			break;
		udelay(5);
	}

	if ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) !=
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE) {
		DP(NETIF_MSG_LINK,
			 "Got bad status 0x%x when reading from SFP+ EEPROM\n",
			 (val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK));
		return -EFAULT;
	}

	/* Read the buffer */
	for (i = 0; i < byte_cnt; i++) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF + i, &val);
		o_buf[i] = (u8)(val & MDIO_PMA_REG_8727_TWO_WIRE_DATA_MASK);
	}

	for (i = 0; i < 100; i++) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		if ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IDLE)
			return 0;
		usleep_range(1000, 2000);
	}

	return -EINVAL;
}