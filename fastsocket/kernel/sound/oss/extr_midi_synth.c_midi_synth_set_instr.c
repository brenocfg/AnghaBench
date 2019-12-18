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
 TYPE_1__** synth_devs ; 

int
midi_synth_set_instr(int dev, int channel, int instr_no)
{
	int             orig_dev = synth_devs[dev]->midi_dev;

	if (instr_no < 0 || instr_no > 127)
		instr_no = 0;
	if (channel < 0 || channel > 15)
		return 0;

	leave_sysex(dev);

	if (!prefix_cmd(orig_dev, 0xc0 | (channel & 0x0f)))
		return 0;
	midi_outc(orig_dev, 0xc0 | (channel & 0x0f));	/*
							 * Program change
							 */
	midi_outc(orig_dev, instr_no);

	return 0;
}