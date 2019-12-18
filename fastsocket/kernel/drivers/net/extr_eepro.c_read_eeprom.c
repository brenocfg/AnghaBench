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
struct net_device {int dummy; } ;
struct eepro_local {int eeprom_reg; } ;

/* Variables and functions */
 short EECS ; 
 short EEDI ; 
 int EEDO ; 
 short EESK ; 
 int EE_READ_CMD ; 
 short STATUS_REG ; 
 int /*<<< orphan*/  eepro_sw2bank0 (int) ; 
 int /*<<< orphan*/  eepro_sw2bank1 (int) ; 
 int /*<<< orphan*/  eepro_sw2bank2 (int) ; 
 int /*<<< orphan*/  eeprom_delay () ; 
 int inb (short) ; 
 struct eepro_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (short,short) ; 

__attribute__((used)) static int
read_eeprom(int ioaddr, int location, struct net_device *dev)
{
	int i;
	unsigned short retval = 0;
	struct eepro_local *lp = netdev_priv(dev);
	short ee_addr = ioaddr + lp->eeprom_reg;
	int read_cmd = location | EE_READ_CMD;
	short ctrl_val = EECS ;

	/* XXXX - black magic */
		eepro_sw2bank1(ioaddr);
		outb(0x00, ioaddr + STATUS_REG);
	/* XXXX - black magic */

	eepro_sw2bank2(ioaddr);
	outb(ctrl_val, ee_addr);

	/* Shift the read command bits out. */
	for (i = 8; i >= 0; i--) {
		short outval = (read_cmd & (1 << i)) ? ctrl_val | EEDI
			: ctrl_val;
		outb(outval, ee_addr);
		outb(outval | EESK, ee_addr);	/* EEPROM clock tick. */
		eeprom_delay();
		outb(outval, ee_addr);	/* Finish EEPROM a clock tick. */
		eeprom_delay();
	}
	outb(ctrl_val, ee_addr);

	for (i = 16; i > 0; i--) {
		outb(ctrl_val | EESK, ee_addr);	 eeprom_delay();
		retval = (retval << 1) | ((inb(ee_addr) & EEDO) ? 1 : 0);
		outb(ctrl_val, ee_addr);  eeprom_delay();
	}

	/* Terminate the EEPROM access. */
	ctrl_val &= ~EECS;
	outb(ctrl_val | EESK, ee_addr);
	eeprom_delay();
	outb(ctrl_val, ee_addr);
	eeprom_delay();
	eepro_sw2bank0(ioaddr);
	return retval;
}