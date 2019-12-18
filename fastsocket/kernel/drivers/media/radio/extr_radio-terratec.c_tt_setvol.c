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
struct terratec {int curvol; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  tt_write_vol (struct terratec*,int) ; 

__attribute__((used)) static int tt_setvol(struct terratec *tt, int vol)
{
	if (vol == tt->curvol) {	/* requested volume = current */
		if (tt->muted) {	/* user is unmuting the card  */
			tt->muted = 0;
			tt_write_vol(tt, vol);	/* enable card */
		}
		return 0;
	}

	if (vol == 0) {			/* volume = 0 means mute the card */
		tt_write_vol(tt, 0);	/* "turn off card" by setting vol to 0 */
		tt->curvol = vol;	/* track the volume state!	*/
		return 0;
	}

	tt->muted = 0;
	tt_write_vol(tt, vol);
	tt->curvol = vol;
	return 0;
}