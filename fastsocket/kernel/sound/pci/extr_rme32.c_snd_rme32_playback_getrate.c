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
struct rme32 {int wcreg; } ;

/* Variables and functions */
 int RME32_WCR_BITPOS_FREQ_0 ; 
 int RME32_WCR_BITPOS_FREQ_1 ; 
 int RME32_WCR_DS_BM ; 

__attribute__((used)) static int snd_rme32_playback_getrate(struct rme32 * rme32)
{
	int rate;

	rate = ((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_0) & 1) +
	       (((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_1) & 1) << 1);
	switch (rate) {
	case 1:
		rate = 32000;
		break;
	case 2:
		rate = 44100;
		break;
	case 3:
		rate = 48000;
		break;
	default:
		return -1;
	}
	return (rme32->wcreg & RME32_WCR_DS_BM) ? rate << 1 : rate;
}