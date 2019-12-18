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
struct MidiBuffer {int command_prev; } ;

/* Variables and functions */

int midibuf_skip_message(struct MidiBuffer *this, unsigned short mask)
{
	int cmd = this->command_prev;

	if ((cmd >= 0x80) && (cmd < 0xf0))
		if ((mask & (1 << (cmd & 0x0f))) == 0)
			return 1;

	return 0;
}