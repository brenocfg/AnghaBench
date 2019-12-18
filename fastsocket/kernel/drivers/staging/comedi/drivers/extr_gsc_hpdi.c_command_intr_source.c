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
 scalar_t__ command_channel_valid (unsigned int) ; 

int command_intr_source(unsigned int channel)
{
	if (command_channel_valid(channel) == 0)
		channel = 1;
	return channel + 1;
}