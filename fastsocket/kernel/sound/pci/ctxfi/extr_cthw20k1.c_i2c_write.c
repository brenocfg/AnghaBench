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
typedef  int u32 ;
struct hw {int dummy; } ;

/* Variables and functions */
 unsigned int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 

__attribute__((used)) static void i2c_write(struct hw *hw, u32 device, u32 addr, u32 data)
{
	unsigned int ret;

	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000));
	hw_write_pci(hw, 0xE0, device);
	hw_write_pci(hw, 0xE4, (data << 8) | (addr & 0xff));
}