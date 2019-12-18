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
 int /*<<< orphan*/  printk (char*) ; 

int command_channel_valid(unsigned int channel)
{
	if (channel == 0 || channel > 6) {
		printk("gsc_hpdi: bug! invalid cable command channel\n");
		return 0;
	}
	return 1;
}