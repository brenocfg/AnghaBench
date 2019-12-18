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
struct replay {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  tempo; } ;

/* Variables and functions */
 scalar_t__ calculate_tick_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replay_set_sequence_pos (struct replay*,int /*<<< orphan*/ ) ; 
 int replay_tick (struct replay*) ; 

int replay_calculate_duration( struct replay *replay ) {
	int count = 0, duration = 0;
	replay_set_sequence_pos( replay, 0 );
	while( count < 1 ) {
		duration += calculate_tick_len( replay->tempo, replay->sample_rate );
		count = replay_tick( replay );
	}
	replay_set_sequence_pos( replay, 0 );
	return duration;
}