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
struct channel {scalar_t__ fadeout_vol; int /*<<< orphan*/  key_on; void* pan_env_tick; TYPE_1__* instrument; void* vol_env_tick; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {scalar_t__ vol_fadeout; TYPE_2__ pan_env; TYPE_2__ vol_env; } ;

/* Variables and functions */
 void* envelope_next_tick (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void channel_update_envelopes( struct channel *channel ) {
	if( channel->instrument->vol_env.enabled ) {
		if( !channel->key_on ) {
			channel->fadeout_vol -= channel->instrument->vol_fadeout;
			if( channel->fadeout_vol < 0 ) {
				channel->fadeout_vol = 0;
			}
		}
		channel->vol_env_tick = envelope_next_tick( &channel->instrument->vol_env,
			channel->vol_env_tick, channel->key_on );
	}
	if( channel->instrument->pan_env.enabled ) {
		channel->pan_env_tick = envelope_next_tick( &channel->instrument->pan_env,
			channel->pan_env_tick, channel->key_on );
	}
}