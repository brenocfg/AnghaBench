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
struct address_info {int io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int init_deskpro(struct address_info *hw_config)
{
	unsigned char   tmp;

	if ((tmp = inb(0xc44)) == 0xff)
	{
		DDB(printk("init_deskpro: Dead port 0xc44\n"));
		return 0;
	}
	outb((tmp | 0x04), 0xc44);	/* Select bank 1 */
	if (inb(0xc44) != 0x04)
	{
		DDB(printk("init_deskpro: Invalid bank1 signature in port 0xc44\n"));
		return 0;
	}
	/*
	 * OK. It looks like a Deskpro so let's proceed.
	 */

	/*
	 * I/O port 0xc44 Audio configuration register.
	 *
	 * bits 0xc0:   Audio revision bits
	 *              0x00 = Compaq Business Audio
	 *              0x40 = MS Sound System Compatible (reset default)
	 *              0x80 = Reserved
	 *              0xc0 = Reserved
	 * bit 0x20:    No Wait State Enable
	 *              0x00 = Disabled (reset default, DMA mode)
	 *              0x20 = Enabled (programmed I/O mode)
	 * bit 0x10:    MS Sound System Decode Enable
	 *              0x00 = Decoding disabled (reset default)
	 *              0x10 = Decoding enabled
	 * bit 0x08:    FM Synthesis Decode Enable
	 *              0x00 = Decoding Disabled (reset default)
	 *              0x08 = Decoding enabled
	 * bit 0x04     Bank select
	 *              0x00 = Bank 0
	 *              0x04 = Bank 1
	 * bits 0x03    MSS Base address
	 *              0x00 = 0x530 (reset default)
	 *              0x01 = 0x604
	 *              0x02 = 0xf40
	 *              0x03 = 0xe80
	 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc44 (before): ");
	outb((tmp & ~0x04), 0xc44);
	printk("%02x ", inb(0xc44));
	outb((tmp | 0x04), 0xc44);
	printk("%02x\n", inb(0xc44));
#endif

	/* Set bank 1 of the register */
	tmp = 0x58;		/* MSS Mode, MSS&FM decode enabled */

	switch (hw_config->io_base)
	{
		case 0x530:
			tmp |= 0x00;
			break;
		case 0x604:
			tmp |= 0x01;
			break;
		case 0xf40:
			tmp |= 0x02;
			break;
		case 0xe80:
			tmp |= 0x03;
			break;
		default:
			DDB(printk("init_deskpro: Invalid MSS port %x\n", hw_config->io_base));
			return 0;
	}
	outb((tmp & ~0x04), 0xc44);	/* Write to bank=0 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc44 (after): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc44));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc44));
#endif

	/*
	 * I/O port 0xc45 FM Address Decode/MSS ID Register.
	 *
	 * bank=0, bits 0xfe:   FM synthesis Decode Compare bits 7:1 (default=0x88)
	 * bank=0, bit 0x01:    SBIC Power Control Bit
	 *                      0x00 = Powered up
	 *                      0x01 = Powered down
	 * bank=1, bits 0xfc:   MSS ID (default=0x40)
	 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc45 (before): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc45));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc45));
#endif

	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	outb((0x88), 0xc45);	/* FM base 7:0 = 0x88 */
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	outb((0x10), 0xc45);	/* MSS ID = 0x10 (MSS port returns 0x04) */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc45 (after): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc45));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc45));
#endif


	/*
	 * I/O port 0xc46 FM Address Decode/Address ASIC Revision Register.
	 *
	 * bank=0, bits 0xff:   FM synthesis Decode Compare bits 15:8 (default=0x03)
	 * bank=1, bits 0xff:   Audio addressing ASIC id
	 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc46 (before): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc46));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc46));
#endif

	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	outb((0x03), 0xc46);	/* FM base 15:8 = 0x03 */
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	outb((0x11), 0xc46);	/* ASIC ID = 0x11 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc46 (after): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc46));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc46));
#endif

	/*
	 * I/O port 0xc47 FM Address Decode Register.
	 *
	 * bank=0, bits 0xff:   Decode enable selection for various FM address bits
	 * bank=1, bits 0xff:   Reserved
	 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc47 (before): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc47));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc47));
#endif

	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	outb((0x7c), 0xc47);	/* FM decode enable bits = 0x7c */
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	outb((0x00), 0xc47);	/* Reserved bank1 = 0x00 */

#ifdef DEBUGXL
	/* Debug printing */
	printk("Port 0xc47 (after): ");
	outb((tmp & ~0x04), 0xc44);	/* Select bank=0 */
	printk("%02x ", inb(0xc47));
	outb((tmp | 0x04), 0xc44);	/* Select bank=1 */
	printk("%02x\n", inb(0xc47));
#endif

	/*
	 * I/O port 0xc6f = Audio Disable Function Register
	 */

#ifdef DEBUGXL
	printk("Port 0xc6f (before) = %02x\n", inb(0xc6f));
#endif

	outb((0x80), 0xc6f);

#ifdef DEBUGXL
	printk("Port 0xc6f (after) = %02x\n", inb(0xc6f));
#endif

	return 1;
}