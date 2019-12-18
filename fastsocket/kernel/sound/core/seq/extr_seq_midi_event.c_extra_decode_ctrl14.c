#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channel; int param; int value; } ;
struct TYPE_4__ {TYPE_1__ control; } ;
struct snd_seq_event {TYPE_2__ data; } ;
struct snd_midi_event {unsigned char lastcmd; scalar_t__ nostat; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MIDI_CMD_CONTROL ; 

__attribute__((used)) static int extra_decode_ctrl14(struct snd_midi_event *dev, unsigned char *buf,
			       int count, struct snd_seq_event *ev)
{
	unsigned char cmd;
	int idx = 0;

	cmd = MIDI_CMD_CONTROL|(ev->data.control.channel & 0x0f);
	if (ev->data.control.param < 0x20) {
		if (count < 4)
			return -ENOMEM;
		if (dev->nostat && count < 6)
			return -ENOMEM;
		if (cmd != dev->lastcmd || dev->nostat) {
			if (count < 5)
				return -ENOMEM;
			buf[idx++] = dev->lastcmd = cmd;
		}
		buf[idx++] = ev->data.control.param;
		buf[idx++] = (ev->data.control.value >> 7) & 0x7f;
		if (dev->nostat)
			buf[idx++] = cmd;
		buf[idx++] = ev->data.control.param + 0x20;
		buf[idx++] = ev->data.control.value & 0x7f;
	} else {
		if (count < 2)
			return -ENOMEM;
		if (cmd != dev->lastcmd || dev->nostat) {
			if (count < 3)
				return -ENOMEM;
			buf[idx++] = dev->lastcmd = cmd;
		}
		buf[idx++] = ev->data.control.param & 0x7f;
		buf[idx++] = ev->data.control.value & 0x7f;
	}
	return idx;
}