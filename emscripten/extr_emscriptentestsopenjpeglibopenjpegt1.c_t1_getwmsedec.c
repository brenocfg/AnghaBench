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

/* Variables and functions */
 double dwt_getnorm (int,int) ; 
 double dwt_getnorm_real (int,int) ; 
 double mct_getnorm (int) ; 
 double mct_getnorm_real (int) ; 

__attribute__((used)) static double t1_getwmsedec(
		int nmsedec,
		int compno,
		int level,
		int orient,
		int bpno,
		int qmfbid,
		double stepsize,
		int numcomps,
		int mct)
{
	double w1, w2, wmsedec;
	if (qmfbid == 1) {
		w1 = (mct && numcomps==3) ? mct_getnorm(compno) : 1.0;
		w2 = dwt_getnorm(level, orient);
	} else {			/* if (qmfbid == 0) */
		w1 = (mct && numcomps==3) ? mct_getnorm_real(compno) : 1.0;
		w2 = dwt_getnorm_real(level, orient);
	}
	wmsedec = w1 * w2 * stepsize * (1 << bpno);
	wmsedec *= wmsedec * nmsedec / 8192.0;
	
	return wmsedec;
}