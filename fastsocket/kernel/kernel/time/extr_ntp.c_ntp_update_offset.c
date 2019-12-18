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
typedef  long s64 ;

/* Variables and functions */
 int /*<<< orphan*/  MAXFREQ_SCALED ; 
 int /*<<< orphan*/  MAXPHASE ; 
 long NSEC_PER_USEC ; 
 int /*<<< orphan*/  NTP_INTERVAL_FREQ ; 
 int NTP_SCALE_SHIFT ; 
 int SHIFT_PLL ; 
 int STA_FREQHOLD ; 
 int STA_NANO ; 
 int STA_PLL ; 
 int /*<<< orphan*/  div_s64 (long,int /*<<< orphan*/ ) ; 
 long get_seconds () ; 
 long max (long,int /*<<< orphan*/ ) ; 
 long min (long,int /*<<< orphan*/ ) ; 
 scalar_t__ ntp_update_offset_fll (long,long) ; 
 int time_constant ; 
 long time_freq ; 
 int /*<<< orphan*/  time_offset ; 
 long time_reftime ; 
 int time_status ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ntp_update_offset(long offset)
{
	s64 freq_adj;
	s64 offset64;
	long secs;

	if (!(time_status & STA_PLL))
		return;

	if (!(time_status & STA_NANO))
		offset *= NSEC_PER_USEC;

	/*
	 * Scale the phase adjustment and
	 * clamp to the operating range.
	 */
	offset = min(offset, MAXPHASE);
	offset = max(offset, -MAXPHASE);

	/*
	 * Select how the frequency is to be controlled
	 * and in which mode (PLL or FLL).
	 */
	secs = get_seconds() - time_reftime;
	if (unlikely(time_status & STA_FREQHOLD))
		secs = 0;

	time_reftime = get_seconds();

	offset64    = offset;
	freq_adj    = (offset64 * secs) <<
			(NTP_SCALE_SHIFT - 2 * (SHIFT_PLL + 2 + time_constant));

	freq_adj    += ntp_update_offset_fll(offset64, secs);

	freq_adj    = min(freq_adj + time_freq, MAXFREQ_SCALED);

	time_freq   = max(freq_adj, -MAXFREQ_SCALED);

	time_offset = div_s64(offset64 << NTP_SCALE_SHIFT, NTP_INTERVAL_FREQ);
}