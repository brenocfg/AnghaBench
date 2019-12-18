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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ command_channel_valid (unsigned int) ; 

uint32_t command_discrete_output_bits(unsigned int channel, int output,
				      int output_value)
{
	uint32_t bits = 0;

	if (command_channel_valid(channel) == 0)
		return 0;
	if (output) {
		bits |= 0x1 << (16 + channel);
		if (output_value)
			bits |= 0x1 << (24 + channel);
	} else
		bits |= 0x1 << (24 + channel);

	return bits;
}