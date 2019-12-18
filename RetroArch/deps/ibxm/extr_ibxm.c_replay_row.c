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
struct replay {scalar_t__ next_row; int break_pos; int seq_pos; size_t row; int** play_count; scalar_t__ pl_count; int tick; int speed; int tempo; int pl_chan; struct channel* channels; struct module* module; } ;
struct pattern {size_t num_rows; } ;
struct note {int effect; int param; } ;
struct module {int sequence_len; size_t* sequence; size_t num_patterns; int num_channels; struct pattern* patterns; } ;
struct channel {int pl_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_row (struct channel*,struct note*) ; 
 int /*<<< orphan*/  pattern_get_note (struct pattern*,int,int,struct note*) ; 

__attribute__((used)) static void replay_row( struct replay *replay ) {
	int idx, count;
	struct note note;
	struct pattern *pattern;
	struct channel *channel;
	struct module *module = replay->module;
	if( replay->next_row < 0 ) {
		replay->break_pos = replay->seq_pos + 1;
		replay->next_row = 0;
	}
	if( replay->break_pos >= 0 ) {
		if( replay->break_pos >= module->sequence_len ) {
			replay->break_pos = replay->next_row = 0;
		}
		while( module->sequence[ replay->break_pos ] >= module->num_patterns ) {
			replay->break_pos++;
			if( replay->break_pos >= module->sequence_len ) {
				replay->break_pos = replay->next_row = 0;
			}
		}
		replay->seq_pos = replay->break_pos;
		for( idx = 0; idx < module->num_channels; idx++ ) {
			replay->channels[ idx ].pl_row = 0;
		}
		replay->break_pos = -1;
	}
	pattern = &module->patterns[ module->sequence[ replay->seq_pos ] ];
	replay->row = replay->next_row;
	if( replay->row >= pattern->num_rows ) {
		replay->row = 0;
	}
	if( replay->play_count && replay->play_count[ 0 ] ) {
		count = replay->play_count[ replay->seq_pos ][ replay->row ];
		if( replay->pl_count < 0 && count < 127 ) {
			replay->play_count[ replay->seq_pos ][ replay->row ] = count + 1;
		}
	}
	replay->next_row = replay->row + 1;
	if( replay->next_row >= pattern->num_rows ) {
		replay->next_row = -1;
	}
	for( idx = 0; idx < module->num_channels; idx++ ) {
		channel = &replay->channels[ idx ];
		pattern_get_note( pattern, replay->row, idx, &note );
		if( note.effect == 0xE ) {
			note.effect = 0x70 | ( note.param >> 4 );
			note.param &= 0xF;
		}
		if( note.effect == 0x93 ) {
			note.effect = 0xF0 | ( note.param >> 4 );
			note.param &= 0xF;
		}
		if( note.effect == 0 && note.param > 0 ) {
			note.effect = 0x8A;
		}
		channel_row( channel, &note );
		switch( note.effect ) {
			case 0x81: /* Set Speed. */
				if( note.param > 0 ) {
					replay->tick = replay->speed = note.param;
				}
				break;
			case 0xB: case 0x82: /* Pattern Jump.*/
				if( replay->pl_count < 0 ) {
					replay->break_pos = note.param;
					replay->next_row = 0;
				}
				break;
			case 0xD: case 0x83: /* Pattern Break.*/
				if( replay->pl_count < 0 ) {
					if( replay->break_pos < 0 ) {
						replay->break_pos = replay->seq_pos + 1;
					}
					replay->next_row = ( note.param >> 4 ) * 10 + ( note.param & 0xF );
				}
				break;
			case 0xF: /* Set Speed/Tempo.*/
				if( note.param > 0 ) {
					if( note.param < 32 ) {
						replay->tick = replay->speed = note.param;
					} else {
						replay->tempo = note.param;
					}
				}
				break;
			case 0x94: /* Set Tempo.*/
				if( note.param > 32 ) {
					replay->tempo = note.param;
				}
				break;
			case 0x76: case 0xFB : /* Pattern Loop.*/
				if( note.param == 0 ) {
					/* Set loop marker on this channel. */
					channel->pl_row = replay->row;
				}
				if( channel->pl_row < replay->row && replay->break_pos < 0 ) {
					/* Marker valid. */
					if( replay->pl_count < 0 ) {
						/* Not already looping, begin. */
						replay->pl_count = note.param;
						replay->pl_chan = idx;
					}
					if( replay->pl_chan == idx ) {
						/* Next Loop.*/
						if( replay->pl_count == 0 ) {
							/* Loop finished. Invalidate current marker. */
							channel->pl_row = replay->row + 1;
						} else {
							/* Loop. */
							replay->next_row = channel->pl_row;
						}
						replay->pl_count--;
					}
				}
				break;
			case 0x7E: case 0xFE: /* Pattern Delay.*/
				replay->tick = replay->speed + replay->speed * note.param;
				break;
		}
	}
}