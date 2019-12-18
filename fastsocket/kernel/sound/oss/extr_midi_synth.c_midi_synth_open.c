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
struct midi_input_info {int m_prev_status; scalar_t__ m_left; scalar_t__ m_ptr; int /*<<< orphan*/  m_state; scalar_t__ m_busy; } ;
struct TYPE_4__ {int (* open ) (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct midi_input_info in_info; } ;
struct TYPE_3__ {int midi_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MST_INIT ; 
 int* midi2synth ; 
 TYPE_2__** midi_devs ; 
 int /*<<< orphan*/  midi_synth_input ; 
 int /*<<< orphan*/  midi_synth_output ; 
 int num_midis ; 
 scalar_t__* prev_out_status ; 
 int stub1 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** synth_devs ; 
 scalar_t__* sysex_state ; 

int
midi_synth_open(int dev, int mode)
{
	int             orig_dev = synth_devs[dev]->midi_dev;
	int             err;
	struct midi_input_info *inc;

	if (orig_dev < 0 || orig_dev > num_midis || midi_devs[orig_dev] == NULL)
		return -ENXIO;

	midi2synth[orig_dev] = dev;
	sysex_state[dev] = 0;
	prev_out_status[orig_dev] = 0;

	if ((err = midi_devs[orig_dev]->open(orig_dev, mode,
			       midi_synth_input, midi_synth_output)) < 0)
		return err;
	inc = &midi_devs[orig_dev]->in_info;

	/* save_flags(flags);
	cli(); 
	don't know against what irqhandler to protect*/
	inc->m_busy = 0;
	inc->m_state = MST_INIT;
	inc->m_ptr = 0;
	inc->m_left = 0;
	inc->m_prev_status = 0x00;
	/* restore_flags(flags); */

	return 1;
}