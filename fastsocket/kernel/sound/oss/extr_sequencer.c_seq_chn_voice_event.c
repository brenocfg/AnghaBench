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
struct TYPE_4__ {int /*<<< orphan*/  (* aftertouch ) (size_t,int,int) ;int /*<<< orphan*/  (* kill_note ) (size_t,int,int,int) ;int /*<<< orphan*/  (* start_note ) (size_t,int,int,int) ;int /*<<< orphan*/  (* setup_voice ) (size_t,int,int) ;TYPE_1__* chn_info; int /*<<< orphan*/  (* set_instr ) (size_t,int,int /*<<< orphan*/ ) ;scalar_t__ alloc_voice; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgm_num; } ;

/* Variables and functions */
#define  MIDI_KEY_PRESSURE 130 
#define  MIDI_NOTEOFF 129 
#define  MIDI_NOTEON 128 
 scalar_t__ SEQ_2 ; 
 int alloc_voice (size_t,int,int) ; 
 int chn ; 
 int cmd ; 
 size_t dev ; 
 int find_voice (size_t,int,int) ; 
 int max_synthdev ; 
 int note ; 
 int num_synths ; 
 int parm ; 
 scalar_t__ seq_mode ; 
 int /*<<< orphan*/  stub1 (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (size_t,int,int) ; 
 int /*<<< orphan*/  stub3 (size_t,int,int,int) ; 
 int /*<<< orphan*/  stub4 (size_t,int,int,int) ; 
 int /*<<< orphan*/  stub5 (size_t,int,int) ; 
 TYPE_2__** synth_devs ; 
 int synth_open_mask ; 

__attribute__((used)) static void seq_chn_voice_event(unsigned char *event_rec)
{
#define dev event_rec[1]
#define cmd event_rec[2]
#define chn event_rec[3]
#define note event_rec[4]
#define parm event_rec[5]

	int voice = -1;

	if ((int) dev > max_synthdev || synth_devs[dev] == NULL)
		return;
	if (!(synth_open_mask & (1 << dev)))
		return;
	if (!synth_devs[dev])
		return;

	if (seq_mode == SEQ_2)
	{
		if (synth_devs[dev]->alloc_voice)
			voice = find_voice(dev, chn, note);

		if (cmd == MIDI_NOTEON && parm == 0)
		{
			cmd = MIDI_NOTEOFF;
			parm = 64;
		}
	}

	switch (cmd)
	{
		case MIDI_NOTEON:
			if (note > 127 && note != 255)	/* Not a seq2 feature */
				return;

			if (voice == -1 && seq_mode == SEQ_2 && synth_devs[dev]->alloc_voice)
			{
				/* Internal synthesizer (FM, GUS, etc) */
				voice = alloc_voice(dev, chn, note);
			}
			if (voice == -1)
				voice = chn;

			if (seq_mode == SEQ_2 && (int) dev < num_synths)
			{
				/*
				 * The MIDI channel 10 is a percussive channel. Use the note
				 * number to select the proper patch (128 to 255) to play.
				 */

				if (chn == 9)
				{
					synth_devs[dev]->set_instr(dev, voice, 128 + note);
					synth_devs[dev]->chn_info[chn].pgm_num = 128 + note;
				}
				synth_devs[dev]->setup_voice(dev, voice, chn);
			}
			synth_devs[dev]->start_note(dev, voice, note, parm);
			break;

		case MIDI_NOTEOFF:
			if (voice == -1)
				voice = chn;
			synth_devs[dev]->kill_note(dev, voice, note, parm);
			break;

		case MIDI_KEY_PRESSURE:
			if (voice == -1)
				voice = chn;
			synth_devs[dev]->aftertouch(dev, voice, parm);
			break;

		default:;
	}
#undef dev
#undef cmd
#undef chn
#undef note
#undef parm
}