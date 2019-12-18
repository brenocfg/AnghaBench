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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PNX4008_PIO_BASE ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_reset(void)
{
	u32 *dum_pio_base = (u32 *)IO_ADDRESS(PNX4008_PIO_BASE);

	udelay(1);
	iowrite32(BIT(19), &dum_pio_base[2]);
	udelay(1);
	iowrite32(BIT(19), &dum_pio_base[1]);
	udelay(1);
}