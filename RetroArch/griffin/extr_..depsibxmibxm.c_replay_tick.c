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
struct replay {scalar_t__ tick; scalar_t__ speed; int** play_count; size_t seq_pos; size_t row; int /*<<< orphan*/ * channels; TYPE_1__* module; } ;
struct TYPE_2__ {int num_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  channel_tick (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_row (struct replay*) ; 

__attribute__((used)) static int replay_tick( struct replay *replay ) {
	int idx, num_channels, count = 1;
	if( --replay->tick <= 0 ) {
		replay->tick = replay->speed;
		replay_row( replay );
	} else {
		num_channels = replay->module->num_channels;
		for( idx = 0; idx < num_channels; idx++ ) {
			channel_tick( &replay->channels[ idx ] );
		}
	}
	if( replay->play_count && replay->play_count[ 0 ] ) {
		count = replay->play_count[ replay->seq_pos ][ replay->row ] - 1;
	}
	return count;
}