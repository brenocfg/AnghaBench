#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* converter; } ;
struct TYPE_5__ {TYPE_1__* chn_info; scalar_t__ emulation; scalar_t__ sysex_ptr; } ;
struct TYPE_4__ {int bender_value; int bender_range; int /*<<< orphan*/  controllers; scalar_t__ pgm_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_2 ; 
 scalar_t__ max_mididev ; 
 int max_synthdev ; 
 TYPE_3__** midi_devs ; 
 int num_midis ; 
 int num_synths ; 
 int /*<<< orphan*/  reset_controllers (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_mode ; 
 TYPE_2__** synth_devs ; 

__attribute__((used)) static void setup_mode2(void)
{
	int dev;

	max_synthdev = num_synths;

	for (dev = 0; dev < num_midis; dev++)
	{
		if (midi_devs[dev] && midi_devs[dev]->converter != NULL)
		{
			synth_devs[max_synthdev++] = midi_devs[dev]->converter;
		}
	}

	for (dev = 0; dev < max_synthdev; dev++)
	{
		int chn;

		synth_devs[dev]->sysex_ptr = 0;
		synth_devs[dev]->emulation = 0;

		for (chn = 0; chn < 16; chn++)
		{
			synth_devs[dev]->chn_info[chn].pgm_num = 0;
			reset_controllers(dev,
				synth_devs[dev]->chn_info[chn].controllers,0);
			synth_devs[dev]->chn_info[chn].bender_value = (1 << 7);	/* Neutral */
			synth_devs[dev]->chn_info[chn].bender_range = 200;
		}
	}
	max_mididev = 0;
	seq_mode = SEQ_2;
}