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
struct snd_midi_op {int dummy; } ;
struct snd_midi_channel_set {scalar_t__ midi_mode; } ;
struct snd_midi_channel {int* control; int gm_rpn_pitch_bend_range; int gm_rpn_fine_tuning; int gm_rpn_coarse_tuning; } ;

/* Variables and functions */
 size_t MIDI_CTL_LSB_DATA_ENTRY ; 
 size_t MIDI_CTL_MSB_DATA_ENTRY ; 
 size_t MIDI_CTL_REGIST_PARM_NUM_LSB ; 
 size_t MIDI_CTL_REGIST_PARM_NUM_MSB ; 
 scalar_t__ SNDRV_MIDI_MODE_NONE ; 

__attribute__((used)) static void
rpn(struct snd_midi_op *ops, void *drv, struct snd_midi_channel *chan,
    struct snd_midi_channel_set *chset)
{
	int type;
	int val;

	if (chset->midi_mode != SNDRV_MIDI_MODE_NONE) {
		type = (chan->control[MIDI_CTL_REGIST_PARM_NUM_MSB] << 8) |
			chan->control[MIDI_CTL_REGIST_PARM_NUM_LSB];
		val = (chan->control[MIDI_CTL_MSB_DATA_ENTRY] << 7) |
			chan->control[MIDI_CTL_LSB_DATA_ENTRY];

		switch (type) {
		case 0x0000: /* Pitch bend sensitivity */
			/* MSB only / 1 semitone per 128 */
			chan->gm_rpn_pitch_bend_range = val;
			break;
					
		case 0x0001: /* fine tuning: */
			/* MSB/LSB, 8192=center, 100/8192 cent step */
			chan->gm_rpn_fine_tuning = val - 8192;
			break;

		case 0x0002: /* coarse tuning */
			/* MSB only / 8192=center, 1 semitone per 128 */
			chan->gm_rpn_coarse_tuning = val - 8192;
			break;

		case 0x7F7F: /* "lock-in" RPN */
			/* ignored */
			break;
		}
	}
	/* should call nrpn or rpn callback here.. */
}