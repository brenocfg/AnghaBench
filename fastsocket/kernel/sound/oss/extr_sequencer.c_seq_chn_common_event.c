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
struct TYPE_5__ {int max_voice; int* map; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bender ) (unsigned char,unsigned char,unsigned short) ;TYPE_2__ alloc; TYPE_1__* chn_info; int /*<<< orphan*/  (* controller ) (unsigned char,unsigned char,unsigned char,unsigned short) ;int /*<<< orphan*/  (* set_instr ) (unsigned char,unsigned char,unsigned char) ;} ;
struct TYPE_4__ {unsigned char pgm_num; unsigned short* controllers; unsigned short bender_value; } ;

/* Variables and functions */
#define  MIDI_CTL_CHANGE 130 
#define  MIDI_PGM_CHANGE 129 
#define  MIDI_PITCH_BEND 128 
 int /*<<< orphan*/  SEQ_2 ; 
 int max_synthdev ; 
 int num_synths ; 
 int /*<<< orphan*/  seq_mode ; 
 int /*<<< orphan*/  stub1 (unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub2 (unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub3 (unsigned char,int,unsigned char,int) ; 
 int /*<<< orphan*/  stub4 (unsigned char,unsigned char,unsigned char,unsigned short) ; 
 int /*<<< orphan*/  stub5 (unsigned char,unsigned char,unsigned char,unsigned short) ; 
 int /*<<< orphan*/  stub6 (unsigned char,int,unsigned short) ; 
 int /*<<< orphan*/  stub7 (unsigned char,unsigned char,unsigned short) ; 
 int /*<<< orphan*/  stub8 (unsigned char,unsigned char,unsigned short) ; 
 TYPE_3__** synth_devs ; 
 int synth_open_mask ; 

__attribute__((used)) static void seq_chn_common_event(unsigned char *event_rec)
{
	unsigned char dev = event_rec[1];
	unsigned char cmd = event_rec[2];
	unsigned char chn = event_rec[3];
	unsigned char p1 = event_rec[4];

	/* unsigned char p2 = event_rec[5]; */
	unsigned short w14 = *(short *) &event_rec[6];

	if ((int) dev > max_synthdev || synth_devs[dev] == NULL)
		return;
	if (!(synth_open_mask & (1 << dev)))
		return;
	if (!synth_devs[dev])
		return;

	switch (cmd)
	{
		case MIDI_PGM_CHANGE:
			if (seq_mode == SEQ_2)
			{
				synth_devs[dev]->chn_info[chn].pgm_num = p1;
				if ((int) dev >= num_synths)
					synth_devs[dev]->set_instr(dev, chn, p1);
			}
			else
				synth_devs[dev]->set_instr(dev, chn, p1);

			break;

		case MIDI_CTL_CHANGE:
			if (seq_mode == SEQ_2)
			{
				if (chn > 15 || p1 > 127)
					break;

				synth_devs[dev]->chn_info[chn].controllers[p1] = w14 & 0x7f;

				if (p1 < 32)	/* Setting MSB should clear LSB to 0 */
					synth_devs[dev]->chn_info[chn].controllers[p1 + 32] = 0;

				if ((int) dev < num_synths)
				{
					int val = w14 & 0x7f;
					int i, key;

					if (p1 < 64)	/* Combine MSB and LSB */
					{
						val = ((synth_devs[dev]->
							chn_info[chn].controllers[p1 & ~32] & 0x7f) << 7)
							| (synth_devs[dev]->
							chn_info[chn].controllers[p1 | 32] & 0x7f);
						p1 &= ~32;
					}
					/* Handle all playing notes on this channel */

					key = ((int) chn << 8);

					for (i = 0; i < synth_devs[dev]->alloc.max_voice; i++)
						if ((synth_devs[dev]->alloc.map[i] & 0xff00) == key)
							synth_devs[dev]->controller(dev, i, p1, val);
				}
				else
					synth_devs[dev]->controller(dev, chn, p1, w14);
			}
			else	/* Mode 1 */
				synth_devs[dev]->controller(dev, chn, p1, w14);
			break;

		case MIDI_PITCH_BEND:
			if (seq_mode == SEQ_2)
			{
				synth_devs[dev]->chn_info[chn].bender_value = w14;

				if ((int) dev < num_synths)
				{
					/* Handle all playing notes on this channel */
					int i, key;

					key = (chn << 8);

					for (i = 0; i < synth_devs[dev]->alloc.max_voice; i++)
						if ((synth_devs[dev]->alloc.map[i] & 0xff00) == key)
							synth_devs[dev]->bender(dev, i, w14);
				}
				else
					synth_devs[dev]->bender(dev, chn, w14);
			}
			else	/* MODE 1 */
				synth_devs[dev]->bender(dev, chn, w14);
			break;

		default:;
	}
}