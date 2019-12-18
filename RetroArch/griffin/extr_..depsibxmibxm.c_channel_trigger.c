#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sample {int volume; int panning; int loop_length; int fine_tune; int rel_note; } ;
struct TYPE_8__ {int instrument; int key; int effect; int param; int volume; } ;
struct channel {int volume; int panning; int period; int sample_off; int fadeout_vol; int key_on; int offset_param; int vibrato_speed; int vibrato_depth; int tone_porta_param; int porta_period; int sample_idx; int vibrato_type; int tremolo_type; scalar_t__ av_count; scalar_t__ retrig_count; scalar_t__ tremolo_phase; scalar_t__ vibrato_phase; scalar_t__ sample_fra; TYPE_2__* replay; struct sample* sample; TYPE_4__ note; TYPE_3__* instrument; scalar_t__ pan_env_tick; scalar_t__ vol_env_tick; } ;
struct TYPE_7__ {int* key_to_sample; struct sample* samples; } ;
struct TYPE_6__ {TYPE_1__* module; } ;
struct TYPE_5__ {int num_instruments; scalar_t__ linear_periods; TYPE_3__* instruments; } ;

/* Variables and functions */
 int FP_SHIFT ; 
 int /*<<< orphan*/  channel_vibrato (struct channel*,int /*<<< orphan*/ ) ; 
 int exp_2 (int) ; 

__attribute__((used)) static void channel_trigger( struct channel *channel ) {
	int key, sam, porta, period, fine_tune, ins = channel->note.instrument;
	struct sample *sample;
	if( ins > 0 && ins <= channel->replay->module->num_instruments ) {
		channel->instrument = &channel->replay->module->instruments[ ins ];
		key = channel->note.key < 97 ? channel->note.key : 0;
		sam = channel->instrument->key_to_sample[ key ];
		sample = &channel->instrument->samples[ sam ];
		channel->volume = sample->volume >= 64 ? 64 : sample->volume & 0x3F;
		if( sample->panning > 0 ) {
			channel->panning = ( sample->panning - 1 ) & 0xFF;
		}
		if( channel->period > 0 && sample->loop_length > 1 ) {
			/* Amiga trigger.*/
			channel->sample = sample;
		}
		channel->sample_off = 0;
		channel->vol_env_tick = channel->pan_env_tick = 0;
		channel->fadeout_vol = 32768;
		channel->key_on = 1;
	}
	if( channel->note.effect == 0x09 || channel->note.effect == 0x8F ) {
		/* Set Sample Offset. */
		if( channel->note.param > 0 ) {
			channel->offset_param = channel->note.param;
		}
		channel->sample_off = channel->offset_param << 8;
	}
	if( channel->note.volume >= 0x10 && channel->note.volume < 0x60 ) {
		channel->volume = channel->note.volume < 0x50 ? channel->note.volume - 0x10 : 64;
	}
	switch( channel->note.volume & 0xF0 ) {
		case 0x80: /* Fine Vol Down.*/
			channel->volume -= channel->note.volume & 0xF;
			if( channel->volume < 0 ) {
				channel->volume = 0;
			}
			break;
		case 0x90: /* Fine Vol Up.*/
			channel->volume += channel->note.volume & 0xF;
			if( channel->volume > 64 ) {
				channel->volume = 64;
			}
			break;
		case 0xA0: /* Set Vibrato Speed.*/
			if( ( channel->note.volume & 0xF ) > 0 ) {
				channel->vibrato_speed = channel->note.volume & 0xF;
			}
			break;
		case 0xB0: /* Vibrato.*/
			if( ( channel->note.volume & 0xF ) > 0 ) {
				channel->vibrato_depth = channel->note.volume & 0xF;
			}
			channel_vibrato( channel, 0 );
			break;
		case 0xC0: /* Set Panning.*/
			channel->panning = ( channel->note.volume & 0xF ) * 17;
			break;
		case 0xF0: /* Tone Porta.*/
			if( ( channel->note.volume & 0xF ) > 0 ) {
				channel->tone_porta_param = channel->note.volume & 0xF;
			}
			break;
	}
	if( channel->note.key > 0 ) {
		if( channel->note.key > 96 ) {
			channel->key_on = 0;
		} else {
			porta = ( channel->note.volume & 0xF0 ) == 0xF0 ||
				channel->note.effect == 0x03 || channel->note.effect == 0x05 ||
				channel->note.effect == 0x87 || channel->note.effect == 0x8C;
			if( !porta ) {
				ins = channel->instrument->key_to_sample[ channel->note.key ];
				channel->sample = &channel->instrument->samples[ ins ];
			}
			fine_tune = channel->sample->fine_tune;
			if( channel->note.effect == 0x75 || channel->note.effect == 0xF2 ) {
				/* Set Fine Tune. */
				fine_tune = ( ( channel->note.param & 0xF ) << 4 ) - 128;
			}
			key = channel->note.key + channel->sample->rel_note;
			if( key < 1 ) {
				key = 1;
			}
			if( key > 120 ) {
				key = 120;
			}
			period = ( key << 6 ) + ( fine_tune >> 1 );
			if( channel->replay->module->linear_periods ) {
				channel->porta_period = 7744 - period;
			} else {
				channel->porta_period = 29021 * exp_2( ( period << FP_SHIFT ) / -768 ) >> FP_SHIFT;
			}
			if( !porta ) {
				channel->period = channel->porta_period;
				channel->sample_idx = channel->sample_off;
				channel->sample_fra = 0;
				if( channel->vibrato_type < 4 ) {
					channel->vibrato_phase = 0;
				}
				if( channel->tremolo_type < 4 ) {
					channel->tremolo_phase = 0;
				}
				channel->retrig_count = channel->av_count = 0;
			}
		}
	}
}