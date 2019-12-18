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
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_TIMER0 ; 
 int /*<<< orphan*/  AR5K_TIMER1 ; 
 int /*<<< orphan*/  AR5K_TIMER3 ; 
 int AR5K_TUNE_DMA_BEACON_RESP ; 
 scalar_t__ ath5k_check_timer_win (unsigned int,unsigned int,int,int) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

bool
ath5k_hw_check_beacon_timers(struct ath5k_hw *ah, int intval)
{
	unsigned int nbtt, atim, dma;

	nbtt = ath5k_hw_reg_read(ah, AR5K_TIMER0);
	atim = ath5k_hw_reg_read(ah, AR5K_TIMER3);
	dma = ath5k_hw_reg_read(ah, AR5K_TIMER1) >> 3;

	/* NOTE: SWBA is different. Having a wrong window there does not
	 * stop us from sending data and this condition is caught by
	 * other means (SWBA interrupt) */

	if (ath5k_check_timer_win(nbtt, atim, 1, intval) &&
	    ath5k_check_timer_win(dma, nbtt, AR5K_TUNE_DMA_BEACON_RESP,
				  intval))
		return true; /* O.K. */
	return false;
}