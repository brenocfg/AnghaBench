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
struct rme96 {int wcreg; } ;

/* Variables and functions */
 scalar_t__ RME96_INPUT_ANALOG ; 
 int RME96_WCR_BITPOS_FREQ_0 ; 
 int RME96_WCR_BITPOS_FREQ_1 ; 
 int RME96_WCR_DS ; 
 int RME96_WCR_MASTER ; 
 int snd_rme96_capture_getrate (struct rme96*,int*) ; 
 scalar_t__ snd_rme96_getinputtype (struct rme96*) ; 

__attribute__((used)) static int
snd_rme96_playback_getrate(struct rme96 *rme96)
{
	int rate, dummy;

	if (!(rme96->wcreg & RME96_WCR_MASTER) &&
            snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
	    (rate = snd_rme96_capture_getrate(rme96, &dummy)) > 0)
	{
	        /* slave clock */
	        return rate;
	}
	rate = ((rme96->wcreg >> RME96_WCR_BITPOS_FREQ_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_FREQ_1) & 1) << 1);
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
	return (rme96->wcreg & RME96_WCR_DS) ? rate << 1 : rate;
}