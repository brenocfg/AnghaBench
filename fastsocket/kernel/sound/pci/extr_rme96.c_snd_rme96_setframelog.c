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
struct rme96 {int wcreg; int playback_frlog; int capture_frlog; } ;

/* Variables and functions */
 int RME96_WCR_MODE24 ; 
 int RME96_WCR_MODE24_2 ; 

__attribute__((used)) static void
snd_rme96_setframelog(struct rme96 *rme96,
		      int n_channels,
		      int is_playback)
{
	int frlog;
	
	if (n_channels == 2) {
		frlog = 1;
	} else {
		/* assume 8 channels */
		frlog = 3;
	}
	if (is_playback) {
		frlog += (rme96->wcreg & RME96_WCR_MODE24) ? 2 : 1;
		rme96->playback_frlog = frlog;
	} else {
		frlog += (rme96->wcreg & RME96_WCR_MODE24_2) ? 2 : 1;
		rme96->capture_frlog = frlog;
	}
}