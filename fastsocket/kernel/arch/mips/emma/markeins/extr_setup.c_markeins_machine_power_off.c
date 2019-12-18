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
 int /*<<< orphan*/  markeins_led (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void markeins_machine_power_off(void)
{
	printk("EMMA2RH Mark-eins halted. Please turn off the power.\n");
	markeins_led("poweroff.");
	while (1) ;
}