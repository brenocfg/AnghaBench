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
struct replay {TYPE_1__* module; } ;
struct channel {int id; int random_seed; TYPE_2__* instrument; int /*<<< orphan*/ * sample; int /*<<< orphan*/  panning; struct replay* replay; } ;
struct TYPE_4__ {int /*<<< orphan*/ * samples; } ;
struct TYPE_3__ {TYPE_2__* instruments; int /*<<< orphan*/ * default_panning; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void channel_init( struct channel *channel, struct replay *replay, int idx ) {
	memset( channel, 0, sizeof( struct channel ) );
	channel->replay = replay;
	channel->id = idx;
	channel->panning = replay->module->default_panning[ idx ];
	channel->instrument = &replay->module->instruments[ 0 ];
	channel->sample = &channel->instrument->samples[ 0 ];
	channel->random_seed = ( idx + 1 ) * 0xABCDEF;
}