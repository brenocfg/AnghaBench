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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nic {TYPE_1__* csr; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  eeprom_ctrl_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  e100_write_flush (struct nic*) ; 
 int eecs ; 
 int eedi ; 
 int eesk ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int op_ewds ; 
 int op_ewen ; 
 int op_write ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void e100_eeprom_write(struct nic *nic, u16 addr_len, u16 addr, __le16 data)
{
	u32 cmd_addr_data[3];
	u8 ctrl;
	int i, j;

	/* Three cmds: write/erase enable, write data, write/erase disable */
	cmd_addr_data[0] = op_ewen << (addr_len - 2);
	cmd_addr_data[1] = (((op_write << addr_len) | addr) << 16) |
		le16_to_cpu(data);
	cmd_addr_data[2] = op_ewds << (addr_len - 2);

	/* Bit-bang cmds to write word to eeprom */
	for (j = 0; j < 3; j++) {

		/* Chip select */
		iowrite8(eecs | eesk, &nic->csr->eeprom_ctrl_lo);
		e100_write_flush(nic); udelay(4);

		for (i = 31; i >= 0; i--) {
			ctrl = (cmd_addr_data[j] & (1 << i)) ?
				eecs | eedi : eecs;
			iowrite8(ctrl, &nic->csr->eeprom_ctrl_lo);
			e100_write_flush(nic); udelay(4);

			iowrite8(ctrl | eesk, &nic->csr->eeprom_ctrl_lo);
			e100_write_flush(nic); udelay(4);
		}
		/* Wait 10 msec for cmd to complete */
		msleep(10);

		/* Chip deselect */
		iowrite8(0, &nic->csr->eeprom_ctrl_lo);
		e100_write_flush(nic); udelay(4);
	}
}