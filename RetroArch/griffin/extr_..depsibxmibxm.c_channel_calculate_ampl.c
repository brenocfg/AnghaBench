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
struct channel {int volume; int tremolo_add; int fadeout_vol; int ampl; int panning; int pann; int /*<<< orphan*/  pan_env_tick; TYPE_3__* instrument; TYPE_2__* replay; int /*<<< orphan*/  vol_env_tick; scalar_t__ key_on; } ;
struct TYPE_8__ {scalar_t__ enabled; } ;
struct TYPE_7__ {TYPE_4__ pan_env; TYPE_4__ vol_env; } ;
struct TYPE_6__ {int global_vol; TYPE_1__* module; } ;
struct TYPE_5__ {int gain; } ;

/* Variables and functions */
 int FP_ONE ; 
 int envelope_calculate_ampl (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void channel_calculate_ampl( struct channel *channel ) {
	int vol, range, env_pan = 32, env_vol = channel->key_on ? 64 : 0;
	if( channel->instrument->vol_env.enabled ) {
		env_vol = envelope_calculate_ampl( &channel->instrument->vol_env, channel->vol_env_tick );
	}
	vol = channel->volume + channel->tremolo_add;
	if( vol > 64 ) {
		vol = 64;
	}
	if( vol < 0 ) {
		vol = 0;
	}
	vol = ( vol * channel->replay->module->gain * FP_ONE ) >> 13;
	vol = ( vol * channel->fadeout_vol ) >> 15;
	channel->ampl = ( vol * channel->replay->global_vol * env_vol ) >> 12;
	if( channel->instrument->pan_env.enabled ) {
		env_pan = envelope_calculate_ampl( &channel->instrument->pan_env, channel->pan_env_tick );
	}
	range = ( channel->panning < 128 ) ? channel->panning : ( 255 - channel->panning );
	channel->pann = channel->panning + ( range * ( env_pan - 32 ) >> 5 );
}