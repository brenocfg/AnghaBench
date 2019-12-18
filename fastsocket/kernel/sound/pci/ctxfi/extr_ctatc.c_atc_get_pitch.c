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

__attribute__((used)) static unsigned int
atc_get_pitch(unsigned int input_rate, unsigned int output_rate)
{
	unsigned int pitch;
	int b;

	/* get pitch and convert to fixed-point 8.24 format. */
	pitch = (input_rate / output_rate) << 24;
	input_rate %= output_rate;
	input_rate /= 100;
	output_rate /= 100;
	for (b = 31; ((b >= 0) && !(input_rate >> b)); )
		b--;

	if (b >= 0) {
		input_rate <<= (31 - b);
		input_rate /= output_rate;
		b = 24 - (31 - b);
		if (b >= 0)
			input_rate <<= b;
		else
			input_rate >>= -b;

		pitch |= input_rate;
	}

	return pitch;
}