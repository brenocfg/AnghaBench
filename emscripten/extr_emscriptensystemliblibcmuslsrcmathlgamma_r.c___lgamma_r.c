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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  double double_t ;

/* Variables and functions */
 double a0 ; 
 double a1 ; 
 double a10 ; 
 double a11 ; 
 double a2 ; 
 double a3 ; 
 double a4 ; 
 double a5 ; 
 double a6 ; 
 double a7 ; 
 double a8 ; 
 double a9 ; 
 double log (double) ; 
 double pi ; 
 double r1 ; 
 double r2 ; 
 double r3 ; 
 double r4 ; 
 double r5 ; 
 double r6 ; 
 double s0 ; 
 double s1 ; 
 double s2 ; 
 double s3 ; 
 double s4 ; 
 double s5 ; 
 double s6 ; 
 double sin_pi (double) ; 
 double t0 ; 
 double t1 ; 
 double t10 ; 
 double t11 ; 
 double t12 ; 
 double t13 ; 
 double t14 ; 
 double t2 ; 
 double t3 ; 
 double t4 ; 
 double t5 ; 
 double t6 ; 
 double t7 ; 
 double t8 ; 
 double t9 ; 
 double tc ; 
 int /*<<< orphan*/  tf ; 
 double tt ; 
 double u0 ; 
 double u1 ; 
 double u2 ; 
 double u3 ; 
 double u4 ; 
 double u5 ; 
 double v1 ; 
 double v2 ; 
 double v3 ; 
 double v4 ; 
 double v5 ; 
 double w0 ; 
 double w1 ; 
 double w2 ; 
 double w3 ; 
 double w4 ; 
 double w5 ; 
 double w6 ; 

double __lgamma_r(double x, int *signgamp)
{
	union {double f; uint64_t i;} u = {x};
	double_t t,y,z,nadj,p,p1,p2,p3,q,r,w;
	uint32_t ix;
	int sign,i;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = u.i>>63;
	ix = u.i>>32 & 0x7fffffff;
	if (ix >= 0x7ff00000)
		return x*x;
	if (ix < (0x3ff-70)<<20) {  /* |x|<2**-70, return -log(|x|) */
		if(sign) {
			x = -x;
			*signgamp = -1;
		}
		return -log(x);
	}
	if (sign) {
		x = -x;
		t = sin_pi(x);
		if (t == 0.0) /* -integer */
			return 1.0/(x-x);
		if (t > 0.0)
			*signgamp = -1;
		else
			t = -t;
		nadj = log(pi/(t*x));
	}

	/* purge off 1 and 2 */
	if ((ix == 0x3ff00000 || ix == 0x40000000) && (uint32_t)u.i == 0)
		r = 0;
	/* for x < 2.0 */
	else if (ix < 0x40000000) {
		if (ix <= 0x3feccccc) {   /* lgamma(x) = lgamma(x+1)-log(x) */
			r = -log(x);
			if (ix >= 0x3FE76944) {
				y = 1.0 - x;
				i = 0;
			} else if (ix >= 0x3FCDA661) {
				y = x - (tc-1.0);
				i = 1;
			} else {
				y = x;
				i = 2;
			}
		} else {
			r = 0.0;
			if (ix >= 0x3FFBB4C3) {  /* [1.7316,2] */
				y = 2.0 - x;
				i = 0;
			} else if(ix >= 0x3FF3B4C4) {  /* [1.23,1.73] */
				y = x - tc;
				i = 1;
			} else {
				y = x - 1.0;
				i = 2;
			}
		}
		switch (i) {
		case 0:
			z = y*y;
			p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*a10))));
			p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*a11)))));
			p = y*p1+p2;
			r += (p-0.5*y);
			break;
		case 1:
			z = y*y;
			w = z*y;
			p1 = t0+w*(t3+w*(t6+w*(t9 +w*t12)));    /* parallel comp */
			p2 = t1+w*(t4+w*(t7+w*(t10+w*t13)));
			p3 = t2+w*(t5+w*(t8+w*(t11+w*t14)));
			p = z*p1-(tt-w*(p2+y*p3));
			r += tf + p;
			break;
		case 2:
			p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*u5)))));
			p2 = 1.0+y*(v1+y*(v2+y*(v3+y*(v4+y*v5))));
			r += -0.5*y + p1/p2;
		}
	} else if (ix < 0x40200000) {  /* x < 8.0 */
		i = (int)x;
		y = x - (double)i;
		p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
		q = 1.0+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*r6)))));
		r = 0.5*y+p/q;
		z = 1.0;    /* lgamma(1+s) = log(s) + lgamma(s) */
		switch (i) {
		case 7: z *= y + 6.0;  /* FALLTHRU */
		case 6: z *= y + 5.0;  /* FALLTHRU */
		case 5: z *= y + 4.0;  /* FALLTHRU */
		case 4: z *= y + 3.0;  /* FALLTHRU */
		case 3: z *= y + 2.0;  /* FALLTHRU */
			r += log(z);
			break;
		}
	} else if (ix < 0x43900000) {  /* 8.0 <= x < 2**58 */
		t = log(x);
		z = 1.0/x;
		y = z*z;
		w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*w6)))));
		r = (x-0.5)*(t-1.0)+w;
	} else                         /* 2**58 <= x <= inf */
		r =  x*(log(x)-1.0);
	if (sign)
		r = nadj - r;
	return r;
}