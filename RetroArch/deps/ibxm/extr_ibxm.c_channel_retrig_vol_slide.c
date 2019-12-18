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
struct channel {scalar_t__ retrig_count; scalar_t__ retrig_ticks; scalar_t__ sample_idx; scalar_t__ sample_fra; int retrig_volume; int volume; } ;

/* Variables and functions */

__attribute__((used)) static void channel_retrig_vol_slide( struct channel *channel ) {
	if( channel->retrig_count >= channel->retrig_ticks ) {
		channel->retrig_count = channel->sample_idx = channel->sample_fra = 0;
		switch( channel->retrig_volume ) {
			case 0x1: channel->volume = channel->volume -  1; break;
			case 0x2: channel->volume = channel->volume -  2; break;
			case 0x3: channel->volume = channel->volume -  4; break;
			case 0x4: channel->volume = channel->volume -  8; break;
			case 0x5: channel->volume = channel->volume - 16; break;
			case 0x6: channel->volume = channel->volume * 2 / 3; break;
			case 0x7: channel->volume = channel->volume >> 1; break;
			case 0x8: /* ? */ break;
			case 0x9: channel->volume = channel->volume +  1; break;
			case 0xA: channel->volume = channel->volume +  2; break;
			case 0xB: channel->volume = channel->volume +  4; break;
			case 0xC: channel->volume = channel->volume +  8; break;
			case 0xD: channel->volume = channel->volume + 16; break;
			case 0xE: channel->volume = channel->volume * 3 / 2; break;
			case 0xF: channel->volume = channel->volume << 1; break;
		}
		if( channel->volume <  0 ) {
			channel->volume = 0;
		}
		if( channel->volume > 64 ) {
			channel->volume = 64;
		}
	}
}