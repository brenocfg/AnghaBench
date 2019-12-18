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
 int /*<<< orphan*/  gpio_set_value (unsigned long,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void lms283gf05_reset(unsigned long gpio, bool inverted)
{
	gpio_set_value(gpio, !inverted);
	mdelay(100);
	gpio_set_value(gpio, inverted);
	mdelay(20);
	gpio_set_value(gpio, !inverted);
	mdelay(20);
}