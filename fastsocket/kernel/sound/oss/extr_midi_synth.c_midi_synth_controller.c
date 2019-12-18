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
struct TYPE_2__ {int midi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  leave_sysex (int) ; 
 int /*<<< orphan*/  midi_outc (int,int) ; 
 int /*<<< orphan*/  prefix_cmd (int,int) ; 
 int* prev_out_status ; 
 TYPE_1__** synth_devs ; 

void
midi_synth_controller(int dev, int channel, int ctrl_num, int value)
{
	int             orig_dev = synth_devs[dev]->midi_dev;
	int             chn, msg;

	if (ctrl_num < 0 || ctrl_num > 127)
		return;
	if (channel < 0 || channel > 15)
		return;

	leave_sysex(dev);

	msg = prev_out_status[orig_dev] & 0xf0;
	chn = prev_out_status[orig_dev] & 0x0f;

	if (msg != 0xb0 || chn != channel)
	  {
		  if (!prefix_cmd(orig_dev, 0xb0 | (channel & 0x0f)))
			  return;
		  midi_outc(orig_dev, 0xb0 | (channel & 0x0f));
	} else if (!prefix_cmd(orig_dev, ctrl_num))
		return;

	midi_outc(orig_dev, ctrl_num);
	midi_outc(orig_dev, value & 0x7f);
}