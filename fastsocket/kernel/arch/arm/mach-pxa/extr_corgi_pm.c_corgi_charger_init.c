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
 int CORGI_GPIO_ADC_TEMP_ON ; 
 int CORGI_GPIO_CHRG_ON ; 
 int CORGI_GPIO_CHRG_UKN ; 
 int CORGI_GPIO_KEY_INT ; 
 int GPIO_IN ; 
 int GPIO_OUT ; 
 int /*<<< orphan*/  pxa_gpio_mode (int) ; 

__attribute__((used)) static void corgi_charger_init(void)
{
	pxa_gpio_mode(CORGI_GPIO_ADC_TEMP_ON | GPIO_OUT);
	pxa_gpio_mode(CORGI_GPIO_CHRG_ON | GPIO_OUT);
	pxa_gpio_mode(CORGI_GPIO_CHRG_UKN | GPIO_OUT);
	pxa_gpio_mode(CORGI_GPIO_KEY_INT | GPIO_IN);
}