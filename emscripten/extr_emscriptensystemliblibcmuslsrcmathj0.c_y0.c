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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORDS (int,int,double) ; 
 double common (int,double,int) ; 
 double j0 (double) ; 
 double log (double) ; 
 double tpi ; 
 double u00 ; 
 double u01 ; 
 double u02 ; 
 double u03 ; 
 double u04 ; 
 double u05 ; 
 double u06 ; 
 double v01 ; 
 double v02 ; 
 double v03 ; 
 double v04 ; 

double y0(double x)
{
	double z,u,v;
	uint32_t ix,lx;

	EXTRACT_WORDS(ix, lx, x);

	/* y0(nan)=nan, y0(<0)=nan, y0(0)=-inf, y0(inf)=0 */
	if ((ix<<1 | lx) == 0)
		return -1/0.0;
	if (ix>>31)
		return 0/0.0;
	if (ix >= 0x7ff00000)
		return 1/x;

	if (ix >= 0x40000000) {  /* x >= 2 */
		/* large ulp errors near zeros: 3.958, 7.086,.. */
		return common(ix,x,1);
	}

	/* U(x^2)/V(x^2) + (2/pi)*j0(x)*log(x) */
	if (ix >= 0x3e400000) {  /* x >= 2**-27 */
		/* large ulp error near the first zero, x ~= 0.89 */
		z = x*x;
		u = u00+z*(u01+z*(u02+z*(u03+z*(u04+z*(u05+z*u06)))));
		v = 1.0+z*(v01+z*(v02+z*(v03+z*v04)));
		return u/v + tpi*(j0(x)*log(x));
	}
	return u00 + tpi*log(x);
}