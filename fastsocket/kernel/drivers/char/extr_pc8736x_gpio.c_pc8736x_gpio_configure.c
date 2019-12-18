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
 int /*<<< orphan*/  SIO_GPIO_PIN_CONFIG ; 
 int /*<<< orphan*/  pc8736x_gpio_configure_fn (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pc8736x_gpio_configure(unsigned index, u32 mask, u32 bits)
{
	return pc8736x_gpio_configure_fn(index, mask, bits,
					 SIO_GPIO_PIN_CONFIG);
}