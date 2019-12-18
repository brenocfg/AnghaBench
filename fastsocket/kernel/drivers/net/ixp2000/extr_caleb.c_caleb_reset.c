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

/* Variables and functions */
 int /*<<< orphan*/  CALEB_BURST ; 
 int /*<<< orphan*/  CALEB_INTREN0 ; 
 int /*<<< orphan*/  CALEB_INTREN1 ; 
 int /*<<< orphan*/  CALEB_PHY0RX ; 
 int /*<<< orphan*/  CALEB_PHY0TX ; 
 int /*<<< orphan*/  CALEB_PHY1RX ; 
 int /*<<< orphan*/  CALEB_PHY1TX ; 
 int /*<<< orphan*/  CALEB_RESET ; 
 int /*<<< orphan*/  caleb_reg_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void caleb_reset(void)
{
	/*
	 * Perform a chip reset.
	 */
	caleb_reg_write(CALEB_RESET, 0x02);
	udelay(1);

	/*
	 * Enable all interrupt sources.  This is needed to get
	 * meaningful results out of the status bits (register 6
	 * and 7.)
	 */
	caleb_reg_write(CALEB_INTREN0, 0xff);
	caleb_reg_write(CALEB_INTREN1, 0x07);

	/*
	 * Set RX and TX FIFO thresholds to 1.5kb.
	 */
	caleb_reg_write(CALEB_PHY0RX, 0x11);
	caleb_reg_write(CALEB_PHY1RX, 0x11);
	caleb_reg_write(CALEB_PHY0TX, 0x11);
	caleb_reg_write(CALEB_PHY1TX, 0x11);

	/*
	 * Program SPI-3 burst size.
	 */
	caleb_reg_write(CALEB_BURST, 0);	// 64-byte RBUF mpackets
//	caleb_reg_write(CALEB_BURST, 1);	// 128-byte RBUF mpackets
//	caleb_reg_write(CALEB_BURST, 2);	// 256-byte RBUF mpackets
}