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
struct ec_disable_detector_state {scalar_t__ hit; scalar_t__ good_cycles; scalar_t__ tone_cycle_duration; int /*<<< orphan*/  tone_present; scalar_t__ notch_level; scalar_t__ channel_level; int /*<<< orphan*/  notch; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  biquad2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
echo_can_disable_detector_init(struct ec_disable_detector_state *det)
{
    /* Elliptic notch */
    /* This is actually centred at 2095Hz, but gets the balance we want, due
       to the asymmetric walls of the notch */
	biquad2_init(&det->notch,
		(int32_t) (-0.7600000*32768.0),
		(int32_t) (-0.1183852*32768.0),
		(int32_t) (-0.5104039*32768.0),
		(int32_t) (0.1567596*32768.0),
		(int32_t) (1.0000000*32768.0));

	det->channel_level = 0;
	det->notch_level = 0;
	det->tone_present = FALSE;
	det->tone_cycle_duration = 0;
	det->good_cycles = 0;
	det->hit = 0;
}