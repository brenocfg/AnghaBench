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
struct envelope {int loop_end_tick; int loop_start_tick; int sustain_tick; scalar_t__ sustain; scalar_t__ looped; } ;

/* Variables and functions */

__attribute__((used)) static int envelope_next_tick( struct envelope *envelope, int tick, int key_on ) {
	tick++;
	if( envelope->looped && tick >= envelope->loop_end_tick ) {
		tick = envelope->loop_start_tick;
	}
	if( envelope->sustain && key_on && tick >= envelope->sustain_tick ) {
		tick = envelope->sustain_tick;
	}
	return tick;
}