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
struct TYPE_2__ {int /*<<< orphan*/  data_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWA_DUMMY_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_USAGE ; 
 unsigned short P_IDENT (unsigned short) ; 
 int /*<<< orphan*/  data_set ; 
 TYPE_1__** gpio_array ; 
 size_t gpio_bank (unsigned short) ; 
 int /*<<< orphan*/  gpio_bit (unsigned short) ; 
 int /*<<< orphan*/  port_setup (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void bfin_reset_boot_spi_cs(unsigned short pin)
{
	unsigned short gpio = P_IDENT(pin);
	port_setup(gpio, GPIO_USAGE);
	gpio_array[gpio_bank(gpio)]->data_set = gpio_bit(gpio);
	AWA_DUMMY_READ(data_set);
	udelay(1);
}