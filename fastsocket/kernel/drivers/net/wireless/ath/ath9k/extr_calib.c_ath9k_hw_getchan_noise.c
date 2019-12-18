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
struct ath9k_channel {scalar_t__ noisefloor; } ;
typedef  scalar_t__ s8 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ ATH9K_NF_CAL_NOISE_THRESH ; 
 scalar_t__ ATH_DEFAULT_NOISE_FLOOR ; 
 scalar_t__ ath9k_hw_get_default_nf (struct ath_hw*,struct ath9k_channel*) ; 

s16 ath9k_hw_getchan_noise(struct ath_hw *ah, struct ath9k_channel *chan)
{
	s8 noise = ATH_DEFAULT_NOISE_FLOOR;

	if (chan && chan->noisefloor) {
		s8 delta = chan->noisefloor -
			   ATH9K_NF_CAL_NOISE_THRESH -
			   ath9k_hw_get_default_nf(ah, chan);
		if (delta > 0)
			noise += delta;
	}
	return noise;
}