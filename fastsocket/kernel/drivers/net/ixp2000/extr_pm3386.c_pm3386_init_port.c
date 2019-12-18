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

/* Variables and functions */
 int pm3386_port_reg_read (int,int,int) ; 
 int /*<<< orphan*/  pm3386_port_reg_write (int,int,int,int) ; 
 int pm3386_reg_read (int,int) ; 
 int /*<<< orphan*/  pm3386_reg_write (int,int,int) ; 
 int swaph (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void pm3386_init_port(int port)
{
	int pm = port >> 1;

	/*
	 * Work around ENP2611 bootloader programming MAC address
	 * in reverse.
	 */
	if (pm3386_port_reg_read(port, 0x30a, 0x100) == 0x0000 &&
	    (pm3386_port_reg_read(port, 0x309, 0x100) & 0xff00) == 0x5000) {
		u16 temp[3];

		temp[0] = pm3386_port_reg_read(port, 0x308, 0x100);
		temp[1] = pm3386_port_reg_read(port, 0x309, 0x100);
		temp[2] = pm3386_port_reg_read(port, 0x30a, 0x100);
		pm3386_port_reg_write(port, 0x308, 0x100, swaph(temp[2]));
		pm3386_port_reg_write(port, 0x309, 0x100, swaph(temp[1]));
		pm3386_port_reg_write(port, 0x30a, 0x100, swaph(temp[0]));
	}

	/*
	 * Initialise narrowbanding mode.  See application note 2010486
	 * for more information.  (@@@ We also need to issue a reset
	 * when ROOL or DOOL are detected.)
	 */
	pm3386_port_reg_write(port, 0x708, 0x10, 0xd055);
	udelay(500);
	pm3386_port_reg_write(port, 0x708, 0x10, 0x5055);

	/*
	 * SPI-3 ingress block.  Set 64 bytes SPI-3 burst size
	 * towards SPI-3 bridge.
	 */
	pm3386_port_reg_write(port, 0x122, 0x20, 0x0002);

	/*
	 * Enable ingress protocol checking, and soft reset the
	 * SPI-3 ingress block.
	 */
	pm3386_reg_write(pm, 0x103, 0x0003);
	while (!(pm3386_reg_read(pm, 0x103) & 0x80))
		;

	/*
	 * SPI-3 egress block.  Gather 12288 bytes of the current
	 * packet in the TX fifo before initiating transmit on the
	 * SERDES interface.  (Prevents TX underflows.)
	 */
	pm3386_port_reg_write(port, 0x221, 0x20, 0x0007);

	/*
	 * Enforce odd parity from the SPI-3 bridge, and soft reset
	 * the SPI-3 egress block.
	 */
	pm3386_reg_write(pm, 0x203, 0x000d & ~(4 << (port & 1)));
	while ((pm3386_reg_read(pm, 0x203) & 0x000c) != 0x000c)
		;

	/*
	 * EGMAC block.  Set this channels to reject long preambles,
	 * not send or transmit PAUSE frames, enable preamble checking,
	 * disable frame length checking, enable FCS appending, enable
	 * TX frame padding.
	 */
	pm3386_port_reg_write(port, 0x302, 0x100, 0x0113);

	/*
	 * Soft reset the EGMAC block.
	 */
	pm3386_port_reg_write(port, 0x301, 0x100, 0x8000);
	pm3386_port_reg_write(port, 0x301, 0x100, 0x0000);

	/*
	 * Auto-sense autonegotiation status.
	 */
	pm3386_port_reg_write(port, 0x306, 0x100, 0x0100);

	/*
	 * Allow reception of jumbo frames.
	 */
	pm3386_port_reg_write(port, 0x310, 0x100, 9018);

	/*
	 * Allow transmission of jumbo frames.
	 */
	pm3386_port_reg_write(port, 0x336, 0x100, 9018);

	/* @@@ Should set 0x337/0x437 (RX forwarding threshold.)  */

	/*
	 * Set autonegotiation parameters to 'no PAUSE, full duplex.'
	 */
	pm3386_port_reg_write(port, 0x31c, 0x100, 0x0020);

	/*
	 * Enable and restart autonegotiation.
	 */
	pm3386_port_reg_write(port, 0x318, 0x100, 0x0003);
	pm3386_port_reg_write(port, 0x318, 0x100, 0x0002);
}