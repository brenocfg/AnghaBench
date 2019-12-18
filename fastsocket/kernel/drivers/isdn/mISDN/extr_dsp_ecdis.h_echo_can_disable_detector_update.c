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
struct ec_disable_detector_state {int channel_level; int notch_level; int tone_cycle_duration; int good_cycles; int hit; void* tone_present; int /*<<< orphan*/  notch; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biquad2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
echo_can_disable_detector_update(struct ec_disable_detector_state *det,
int16_t amp)
{
	int16_t notched;

	notched = biquad2(&det->notch, amp);
	/* Estimate the overall energy in the channel, and the energy in
	   the notch (i.e. overall channel energy - tone energy => noise).
	   Use abs instead of multiply for speed (is it really faster?).
	   Damp the overall energy a little more for a stable result.
	   Damp the notch energy a little less, so we don't damp out the
	   blip every time the phase reverses */
	det->channel_level += ((abs(amp) - det->channel_level) >> 5);
	det->notch_level += ((abs(notched) - det->notch_level) >> 4);
	if (det->channel_level > 280) {
		/* There is adequate energy in the channel.
		 Is it mostly at 2100Hz? */
		if (det->notch_level*6 < det->channel_level) {
			/* The notch says yes, so we have the tone. */
			if (!det->tone_present) {
				/* Do we get a kick every 450+-25ms? */
				if (det->tone_cycle_duration >= 425*8
					&& det->tone_cycle_duration <= 475*8) {
					det->good_cycles++;
					if (det->good_cycles > 2)
						det->hit = TRUE;
				}
				det->tone_cycle_duration = 0;
			}
			det->tone_present = TRUE;
		} else
			det->tone_present = FALSE;
		det->tone_cycle_duration++;
	} else {
		det->tone_present = FALSE;
		det->tone_cycle_duration = 0;
		det->good_cycles = 0;
	}
	return det->hit;
}