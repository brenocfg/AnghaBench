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
 int /*<<< orphan*/  GPIO_IRQ_falling_edge ; 
 int /*<<< orphan*/  GPIO_IRQ_level_high ; 
 int /*<<< orphan*/  GPIO_IRQ_level_low ; 
 int /*<<< orphan*/  GPIO_IRQ_rising_edge ; 
 int /*<<< orphan*/  IXP2000_GPIO_FEDR ; 
 int /*<<< orphan*/  IXP2000_GPIO_LSHR ; 
 int /*<<< orphan*/  IXP2000_GPIO_LSLR ; 
 int /*<<< orphan*/  IXP2000_GPIO_REDR ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_gpio_int_csrs(void)
{
	ixp2000_reg_write(IXP2000_GPIO_FEDR, GPIO_IRQ_falling_edge);
	ixp2000_reg_write(IXP2000_GPIO_REDR, GPIO_IRQ_rising_edge);
	ixp2000_reg_write(IXP2000_GPIO_LSLR, GPIO_IRQ_level_low);
	ixp2000_reg_wrb(IXP2000_GPIO_LSHR, GPIO_IRQ_level_high);
}