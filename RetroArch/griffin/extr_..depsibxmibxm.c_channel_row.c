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
struct note {int effect; scalar_t__ param; } ;
struct channel {int porta_up_param; int porta_down_param; int tone_porta_param; int vibrato_speed; int vibrato_depth; int vol_slide_param; int tremolo_speed; int tremolo_depth; int panning; int volume; int gvol_slide_param; int vol_env_tick; int pan_env_tick; int pan_slide_param; int retrig_volume; int retrig_ticks; int tremor_on_ticks; int tremor_off_ticks; int xfine_porta_param; int fine_porta_up_param; int fine_porta_down_param; int vibrato_type; int tremolo_type; int fine_vslide_up_param; int fine_vslide_down_param; int arpeggio_param; struct note note; int /*<<< orphan*/  key_on; TYPE_1__* replay; scalar_t__ fx_count; scalar_t__ arpeggio_add; scalar_t__ tremolo_add; scalar_t__ vibrato_add; int /*<<< orphan*/  retrig_count; } ;
struct TYPE_2__ {int global_vol; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_auto_vibrato (struct channel*) ; 
 int /*<<< orphan*/  channel_calculate_ampl (struct channel*) ; 
 int /*<<< orphan*/  channel_calculate_freq (struct channel*) ; 
 int /*<<< orphan*/  channel_porta_down (struct channel*,int) ; 
 int /*<<< orphan*/  channel_porta_up (struct channel*,int) ; 
 int /*<<< orphan*/  channel_retrig_vol_slide (struct channel*) ; 
 int /*<<< orphan*/  channel_tremolo (struct channel*) ; 
 int /*<<< orphan*/  channel_tremor (struct channel*) ; 
 int /*<<< orphan*/  channel_trigger (struct channel*) ; 
 int /*<<< orphan*/  channel_update_envelopes (struct channel*) ; 
 int /*<<< orphan*/  channel_vibrato (struct channel*,int) ; 
 int /*<<< orphan*/  channel_volume_slide (struct channel*) ; 

__attribute__((used)) static void channel_row( struct channel *channel, struct note *note ) {
	channel->note = *note;
	channel->retrig_count++;
	channel->vibrato_add = channel->tremolo_add = channel->arpeggio_add = channel->fx_count = 0;
	if( !( ( note->effect == 0x7D || note->effect == 0xFD ) && note->param > 0 ) ) {
		/* Not note delay.*/
		channel_trigger( channel );
	}
	switch( channel->note.effect ) {
		case 0x01: case 0x86: /* Porta Up. */
			if( channel->note.param > 0 ) {
				channel->porta_up_param = channel->note.param;
			}
			channel_porta_up( channel, channel->porta_up_param );
			break;
		case 0x02: case 0x85: /* Porta Down. */
			if( channel->note.param > 0 ) {
				channel->porta_down_param = channel->note.param;
			}
			channel_porta_down( channel, channel->porta_down_param );
			break;
		case 0x03: case 0x87: /* Tone Porta. */
			if( channel->note.param > 0 ) {
				channel->tone_porta_param = channel->note.param;
			}
			break;
		case 0x04: case 0x88: /* Vibrato. */
			if( ( channel->note.param >> 4 ) > 0 ) {
				channel->vibrato_speed = channel->note.param >> 4;
			}
			if( ( channel->note.param & 0xF ) > 0 ) {
				channel->vibrato_depth = channel->note.param & 0xF;
			}
			channel_vibrato( channel, 0 );
			break;
		case 0x05: case 0x8C: /* Tone Porta + Vol Slide. */
			if( channel->note.param > 0 ) {
				channel->vol_slide_param = channel->note.param;
			}
			channel_volume_slide( channel );
			break;
		case 0x06: case 0x8B: /* Vibrato + Vol Slide. */
			if( channel->note.param > 0 ) {
				channel->vol_slide_param = channel->note.param;
			}
			channel_vibrato( channel, 0 );
			channel_volume_slide( channel );
			break;
		case 0x07: case 0x92: /* Tremolo. */
			if( ( channel->note.param >> 4 ) > 0 ) {
				channel->tremolo_speed = channel->note.param >> 4;
			}
			if( ( channel->note.param & 0xF ) > 0 ) {
				channel->tremolo_depth = channel->note.param & 0xF;
			}
			channel_tremolo( channel );
			break;
		case 0x08: /* Set Panning.*/
			channel->panning = ( channel->note.param < 128 ) ? ( channel->note.param << 1 ) : 255;
			break;
		case 0x0A: case 0x84: /* Vol Slide. */
			if( channel->note.param > 0 ) {
				channel->vol_slide_param = channel->note.param;
			}
			channel_volume_slide( channel );
			break;
		case 0x0C: /* Set Volume. */
			channel->volume = channel->note.param >= 64 ? 64 : channel->note.param & 0x3F;
			break;
		case 0x10: case 0x96: /* Set Global Volume. */
			channel->replay->global_vol = channel->note.param >= 64 ? 64 : channel->note.param & 0x3F;
			break;
		case 0x11: /* Global Volume Slide. */
			if( channel->note.param > 0 ) {
				channel->gvol_slide_param = channel->note.param;
			}
			break;
		case 0x14: /* Key Off. */
			channel->key_on = 0;
			break;
		case 0x15: /* Set Envelope Tick. */
			channel->vol_env_tick = channel->pan_env_tick = channel->note.param & 0xFF;
			break;
		case 0x19: /* Panning Slide. */
			if( channel->note.param > 0 ) {
				channel->pan_slide_param = channel->note.param;
			}
			break;
		case 0x1B: case 0x91: /* Retrig + Vol Slide. */
			if( ( channel->note.param >> 4 ) > 0 ) {
				channel->retrig_volume = channel->note.param >> 4;
			}
			if( ( channel->note.param & 0xF ) > 0 ) {
				channel->retrig_ticks = channel->note.param & 0xF;
			}
			channel_retrig_vol_slide( channel );
			break;
		case 0x1D: case 0x89: /* Tremor. */
			if( ( channel->note.param >> 4 ) > 0 ) {
				channel->tremor_on_ticks = channel->note.param >> 4;
			}
			if( ( channel->note.param & 0xF ) > 0 ) {
				channel->tremor_off_ticks = channel->note.param & 0xF;
			}
			channel_tremor( channel );
			break;
		case 0x21: /* Extra Fine Porta. */
			if( channel->note.param > 0 ) {
				channel->xfine_porta_param = channel->note.param;
			}
			switch( channel->xfine_porta_param & 0xF0 ) {
				case 0x10:
					channel_porta_up( channel, 0xE0 | ( channel->xfine_porta_param & 0xF ) );
					break;
				case 0x20:
					channel_porta_down( channel, 0xE0 | ( channel->xfine_porta_param & 0xF ) );
					break;
			}
			break;
		case 0x71: /* Fine Porta Up. */
			if( channel->note.param > 0 ) {
				channel->fine_porta_up_param = channel->note.param;
			}
			channel_porta_up( channel, 0xF0 | ( channel->fine_porta_up_param & 0xF ) );
			break;
		case 0x72: /* Fine Porta Down. */
			if( channel->note.param > 0 ) {
				channel->fine_porta_down_param = channel->note.param;
			}
			channel_porta_down( channel, 0xF0 | ( channel->fine_porta_down_param & 0xF ) );
			break;
		case 0x74: case 0xF3: /* Set Vibrato Waveform. */
			if( channel->note.param < 8 ) {
				channel->vibrato_type = channel->note.param;
			}
			break;
		case 0x77: case 0xF4: /* Set Tremolo Waveform. */
			if( channel->note.param < 8 ) {
				channel->tremolo_type = channel->note.param;
			}
			break;
		case 0x7A: /* Fine Vol Slide Up. */
			if( channel->note.param > 0 ) {
				channel->fine_vslide_up_param = channel->note.param;
			}
			channel->volume += channel->fine_vslide_up_param;
			if( channel->volume > 64 ) {
				channel->volume = 64;
			}
			break;
		case 0x7B: /* Fine Vol Slide Down. */
			if( channel->note.param > 0 ) {
				channel->fine_vslide_down_param = channel->note.param;
			}
			channel->volume -= channel->fine_vslide_down_param;
			if( channel->volume < 0 ) {
				channel->volume = 0;
			}
			break;
		case 0x7C: case 0xFC: /* Note Cut. */
			if( channel->note.param <= 0 ) {
				channel->volume = 0;
			}
			break;
		case 0x8A: /* Arpeggio. */
			if( channel->note.param > 0 ) {
				channel->arpeggio_param = channel->note.param;
			}
			break;
		case 0x95: /* Fine Vibrato.*/
			if( ( channel->note.param >> 4 ) > 0 ) {
				channel->vibrato_speed = channel->note.param >> 4;
			}
			if( ( channel->note.param & 0xF ) > 0 ) {
				channel->vibrato_depth = channel->note.param & 0xF;
			}
			channel_vibrato( channel, 1 );
			break;
		case 0xF8: /* Set Panning. */
			channel->panning = channel->note.param * 17;
			break;
	}
	channel_auto_vibrato( channel );
	channel_calculate_freq( channel );
	channel_calculate_ampl( channel );
	channel_update_envelopes( channel );
}