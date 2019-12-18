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
struct wl1251 {int physical_reg_addr; int virtual_reg_addr; } ;

/* Variables and functions */
 int ACX_REG_TABLE_LEN ; 
 int EINVAL ; 
 int REGISTERS_BASE ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 
 int* wl1251_io_reg_table ; 

__attribute__((used)) static int wl1251_translate_reg_addr(struct wl1251 *wl, int addr)
{
	/* If the address is lower than REGISTERS_BASE, it means that this is
	 * a chip-specific register address, so look it up in the registers
	 * table */
	if (addr < REGISTERS_BASE) {
		/* Make sure we don't go over the table */
		if (addr >= ACX_REG_TABLE_LEN) {
			wl1251_error("address out of range (%d)", addr);
			return -EINVAL;
		}
		addr = wl1251_io_reg_table[addr];
	}

	return addr - wl->physical_reg_addr + wl->virtual_reg_addr;
}