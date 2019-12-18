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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASE_ACTIVATE_DELAY ; 
 scalar_t__ IS_CHAN_B (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

void ath9k_hw_synth_delay(struct ath_hw *ah, struct ath9k_channel *chan,
			  int hw_delay)
{
	if (IS_CHAN_B(chan))
		hw_delay = (4 * hw_delay) / 22;
	else
		hw_delay /= 10;

	if (IS_CHAN_HALF_RATE(chan))
		hw_delay *= 2;
	else if (IS_CHAN_QUARTER_RATE(chan))
		hw_delay *= 4;

	udelay(hw_delay + BASE_ACTIVATE_DELAY);
}