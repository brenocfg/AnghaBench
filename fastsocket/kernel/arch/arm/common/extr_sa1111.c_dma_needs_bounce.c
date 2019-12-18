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
struct device {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ machine_is_assabet () ; 
 scalar_t__ machine_is_pfs168 () ; 

int dma_needs_bounce(struct device *dev, dma_addr_t addr, size_t size)
{
	/*
	 * Section 4.6 of the "Intel StrongARM SA-1111 Development Module
	 * User's Guide" mentions that jumpers R51 and R52 control the
	 * target of SA-1111 DMA (either SDRAM bank 0 on Assabet, or
	 * SDRAM bank 1 on Neponset). The default configuration selects
	 * Assabet, so any address in bank 1 is necessarily invalid.
	 */
	return ((machine_is_assabet() || machine_is_pfs168()) &&
		(addr >= 0xc8000000 || (addr + size) >= 0xc8000000));
}