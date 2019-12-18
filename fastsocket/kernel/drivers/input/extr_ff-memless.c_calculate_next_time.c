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
struct ml_effect_state {unsigned long play_at; unsigned long adj_at; unsigned long stop_at; TYPE_2__* effect; } ;
struct ff_envelope {scalar_t__ fade_length; scalar_t__ attack_length; } ;
struct TYPE_3__ {scalar_t__ length; } ;
struct TYPE_4__ {TYPE_1__ replay; } ;

/* Variables and functions */
 scalar_t__ FF_ENVELOPE_INTERVAL ; 
 struct ff_envelope* get_envelope (TYPE_2__*) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long calculate_next_time(struct ml_effect_state *state)
{
	const struct ff_envelope *envelope = get_envelope(state->effect);
	unsigned long attack_stop, fade_start, next_fade;

	if (envelope->attack_length) {
		attack_stop = state->play_at +
			msecs_to_jiffies(envelope->attack_length);
		if (time_before(state->adj_at, attack_stop))
			return state->adj_at +
					msecs_to_jiffies(FF_ENVELOPE_INTERVAL);
	}

	if (state->effect->replay.length) {
		if (envelope->fade_length) {
			/* check when fading should start */
			fade_start = state->stop_at -
					msecs_to_jiffies(envelope->fade_length);

			if (time_before(state->adj_at, fade_start))
				return fade_start;

			/* already fading, advance to next checkpoint */
			next_fade = state->adj_at +
					msecs_to_jiffies(FF_ENVELOPE_INTERVAL);
			if (time_before(next_fade, state->stop_at))
				return next_fade;
		}

		return state->stop_at;
	}

	return state->play_at;
}