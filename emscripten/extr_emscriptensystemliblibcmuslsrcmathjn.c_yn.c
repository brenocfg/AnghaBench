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
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 double cos (double) ; 
 double invsqrtpi ; 
 double sin (double) ; 
 double sqrt (double) ; 
 double y0 (double) ; 
 double y1 (double) ; 

double yn(int n, double x)
{
	uint32_t ix, lx, ib;
	int nm1, sign, i;
	double a, b, temp;

	EXTRACT_WORDS(ix, lx, x);
	sign = ix>>31;
	ix &= 0x7fffffff;

	if ((ix | (lx|-lx)>>31) > 0x7ff00000) /* nan */
		return x;
	if (sign && (ix|lx)!=0) /* x < 0 */
		return 0/0.0;
	if (ix == 0x7ff00000)
		return 0.0;

	if (n == 0)
		return y0(x);
	if (n < 0) {
		nm1 = -(n+1);
		sign = n&1;
	} else {
		nm1 = n-1;
		sign = 0;
	}
	if (nm1 == 0)
		return sign ? -y1(x) : y1(x);

	if (ix >= 0x52d00000) { /* x > 2**302 */
		/* (x >> n**2)
		 *      Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Let s=sin(x), c=cos(x),
		 *          xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
		 *
		 *             n    sin(xn)*sqt2    cos(xn)*sqt2
		 *          ----------------------------------
		 *             0     s-c             c+s
		 *             1    -s-c            -c+s
		 *             2    -s+c            -c-s
		 *             3     s+c             c-s
		 */
		switch(nm1&3) {
		case 0: temp = -sin(x)-cos(x); break;
		case 1: temp = -sin(x)+cos(x); break;
		case 2: temp =  sin(x)+cos(x); break;
		default:
		case 3: temp =  sin(x)-cos(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	} else {
		a = y0(x);
		b = y1(x);
		/* quit if b is -inf */
		GET_HIGH_WORD(ib, b);
		for (i=0; i<nm1 && ib!=0xfff00000; ){
			i++;
			temp = b;
			b = (2.0*i/x)*b - a;
			GET_HIGH_WORD(ib, b);
			a = temp;
		}
	}
	return sign ? -b : b;
}