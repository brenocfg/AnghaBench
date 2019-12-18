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
struct mb86a16_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int swp_freq_calcuation(struct mb86a16_state *state, int i, int v, int *V,  int vmax, int vmin,
			       int SIGMIN, int fOSC, int afcex_freq, int swp_ofs, unsigned char *SIG1)
{
	int swp_freq ;

	if ((i % 2 == 1) && (v <= vmax)) {
		/* positive v (case 1) */
		if ((v - 1 == vmin)				&&
		    (*(V + 30 + v) >= 0)			&&
		    (*(V + 30 + v - 1) >= 0)			&&
		    (*(V + 30 + v - 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v - 1) > SIGMIN)) {

			swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
			*SIG1 = *(V + 30 + v - 1);
		} else if ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 1))	&&
			   (*(V + 30 + v) > SIGMIN)) {
			/* (case 2) */
			swp_freq = fOSC * 1000 + afcex_freq;
			*SIG1 = *(V + 30 + v);
		} else if ((*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v - 1) > 0)		&&
			   (*(V + 30 + v - 2) > 0)		&&
			   (*(V + 30 + v - 3) > 0)		&&
			   (*(V + 30 + v - 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v - 2) > *(V + 30 + v - 3)) &&
			   ((*(V + 30 + v - 1) > SIGMIN)	||
			   (*(V + 30 + v - 2) > SIGMIN))) {
			/* (case 3) */
			if (*(V + 30 + v - 1) >= *(V + 30 + v - 2)) {
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			} else {
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs * 2;
				*SIG1 = *(V + 30 + v - 2);
			}
		} else if ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v - 2) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 2))	&&
			   (*(V + 30 + v - 1) > *(V + 30 + v - 2)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			   (*(V + 30 + v - 1) > SIGMIN))) {
			/* (case 4) */
			if (*(V + 30 + v) >= *(V + 30 + v - 1)) {
				swp_freq = fOSC * 1000 + afcex_freq;
				*SIG1 = *(V + 30 + v);
			} else {
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			}
		} else  {
			swp_freq = -1 ;
		}
	} else if ((i % 2 == 0) && (v >= vmin)) {
		/* Negative v (case 1) */
		if ((*(V + 30 + v) > 0)				&&
		    (*(V + 30 + v + 1) > 0)			&&
		    (*(V + 30 + v + 2) > 0)			&&
		    (*(V + 30 + v + 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v + 1) > *(V + 30 + v + 2))	&&
		    (*(V + 30 + v + 1) > SIGMIN)) {

			swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
			*SIG1 = *(V + 30 + v + 1);
		} else if ((v + 1 == vmax)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 1) > SIGMIN)) {
			/* (case 2) */
			swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
			*SIG1 = *(V + 30 + v);
		} else if ((v == vmin)				&&
			   (*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v + 1) > 0)		&&
			   (*(V + 30 + v + 2) > 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 1))	&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v) > SIGMIN)) {
			/* (case 3) */
			swp_freq = fOSC * 1000 + afcex_freq;
			*SIG1 = *(V + 30 + v);
		} else if ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) {
			/* (case 4) */
			if (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) {
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			} else {
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			}
		} else if ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 2)) &&
			   (*(V + 30 + v) > *(V + 30 + v + 3))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			    (*(V + 30 + v + 1) > SIGMIN))) {
			/* (case 5) */
			if (*(V + 30 + v) >= *(V + 30 + v + 1)) {
				swp_freq = fOSC * 1000 + afcex_freq;
				*SIG1 = *(V + 30 + v);
			} else {
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			}
		} else if ((v + 2 == vmin)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v))	&&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) {
			/* (case 6) */
			if (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) {
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			} else {
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			}
		} else if ((vmax == 0) && (vmin == 0) && (*(V + 30 + v) > SIGMIN)) {
			swp_freq = fOSC * 1000;
			*SIG1 = *(V + 30 + v);
		} else
			swp_freq = -1;
	} else
		swp_freq = -1;

	return swp_freq;
}