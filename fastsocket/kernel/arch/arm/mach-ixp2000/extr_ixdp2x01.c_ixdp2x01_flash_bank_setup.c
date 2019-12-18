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
 unsigned long IXDP2X01_CPLD_FLASH_INTERN ; 
 int /*<<< orphan*/  IXDP2X01_CPLD_FLASH_REG ; 
 unsigned long IXDP2X01_FLASH_WINDOW_BITS ; 
 unsigned long IXDP2X01_FLASH_WINDOW_MASK ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned long ixdp2x01_flash_bank_setup(unsigned long ofs)
{
	ixp2000_reg_wrb(IXDP2X01_CPLD_FLASH_REG,
		((ofs >> IXDP2X01_FLASH_WINDOW_BITS) | IXDP2X01_CPLD_FLASH_INTERN));
	return (ofs & IXDP2X01_FLASH_WINDOW_MASK);
}