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
struct replay {int sample_rate; int /*<<< orphan*/  interpolation; struct channel* channels; TYPE_1__* module; int /*<<< orphan*/  tempo; } ;
struct channel {int dummy; } ;
struct TYPE_2__ {int num_channels; } ;

/* Variables and functions */
 int calculate_tick_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  channel_resample (struct channel*,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_update_sample_idx (struct channel*,int,int) ; 
 int /*<<< orphan*/  downsample (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  replay_tick (struct replay*) ; 
 int /*<<< orphan*/  replay_volume_ramp (struct replay*,int*,int) ; 

int replay_get_audio( struct replay *replay, int *mix_buf ) {
	struct channel *channel;
	int idx, num_channels, tick_len = calculate_tick_len( replay->tempo, replay->sample_rate );
	/* Clear output buffer. */
	memset( mix_buf, 0, ( tick_len + 65 ) * 4 * sizeof( int ) );
	/* Resample. */
	num_channels = replay->module->num_channels;
	for( idx = 0; idx < num_channels; idx++ ) {
		channel = &replay->channels[ idx ];
		channel_resample( channel, mix_buf, 0, ( tick_len + 65 ) * 2,
			replay->sample_rate * 2, replay->interpolation );
		channel_update_sample_idx( channel, tick_len * 2, replay->sample_rate * 2 );
	}
	downsample( mix_buf, tick_len + 64 );
	replay_volume_ramp( replay, mix_buf, tick_len );
	replay_tick( replay );
	return tick_len;
}