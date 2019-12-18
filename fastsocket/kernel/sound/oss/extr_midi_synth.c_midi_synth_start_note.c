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

int
midi_synth_start_note(int dev, int channel, int note, int velocity)
{
	int             orig_dev = synth_devs[dev]->midi_dev;
	int             msg, chn;

	if (note < 0 || note > 127)
		return 0;
	if (channel < 0 || channel > 15)
		return 0;
	if (velocity < 0)
		velocity = 0;
	if (velocity > 127)
		velocity = 127;

	leave_sysex(dev);

	msg = prev_out_status[orig_dev] & 0xf0;
	chn = prev_out_status[orig_dev] & 0x0f;

	if (chn == channel && msg == 0x90)
	  {			/*
				 * Use running status
				 */
		  if (!prefix_cmd(orig_dev, note))
			  return 0;
		  midi_outc(orig_dev, note);
		  midi_outc(orig_dev, velocity);
	} else
	  {
		  if (!prefix_cmd(orig_dev, 0x90 | (channel & 0x0f)))
			  return 0;
		  midi_outc(orig_dev, 0x90 | (channel & 0x0f));		/*
									 * Note on
									 */
		  midi_outc(orig_dev, note);
		  midi_outc(orig_dev, velocity);
	  }
	return 0;
}