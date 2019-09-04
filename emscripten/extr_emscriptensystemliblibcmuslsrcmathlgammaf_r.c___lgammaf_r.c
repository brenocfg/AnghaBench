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
 int /*<<< orphan*/  a0 ; 
 int /*<<< orphan*/  a1 ; 
 float a10 ; 
 float a11 ; 
 int /*<<< orphan*/  a2 ; 
 int /*<<< orphan*/  a3 ; 
 int /*<<< orphan*/  a4 ; 
 int /*<<< orphan*/  a5 ; 
 int /*<<< orphan*/  a6 ; 
 int /*<<< orphan*/  a7 ; 
 int /*<<< orphan*/  a8 ; 
 int /*<<< orphan*/  a9 ; 
 float logf (float) ; 
 float pi ; 
 float r1 ; 
 float r2 ; 
 float r3 ; 
 float r4 ; 
 float r5 ; 
 float r6 ; 
 float s0 ; 
 float s1 ; 
 float s2 ; 
 float s3 ; 
 float s4 ; 
 float s5 ; 
 float s6 ; 
 float sin_pi (float) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  t10 ; 
 int /*<<< orphan*/  t11 ; 
 float t12 ; 
 float t13 ; 
 float t14 ; 
 int /*<<< orphan*/  t2 ; 
 int /*<<< orphan*/  t3 ; 
 int /*<<< orphan*/  t4 ; 
 int /*<<< orphan*/  t5 ; 
 int /*<<< orphan*/  t6 ; 
 int /*<<< orphan*/  t7 ; 
 int /*<<< orphan*/  t8 ; 
 int /*<<< orphan*/  t9 ; 
 float tc ; 
 int /*<<< orphan*/  tf ; 
 int /*<<< orphan*/  tt ; 
 int /*<<< orphan*/  u0 ; 
 int /*<<< orphan*/  u1 ; 
 int /*<<< orphan*/  u2 ; 
 int /*<<< orphan*/  u3 ; 
 int /*<<< orphan*/  u4 ; 
 float u5 ; 
 int /*<<< orphan*/  v1 ; 
 int /*<<< orphan*/  v2 ; 
 int /*<<< orphan*/  v3 ; 
 int /*<<< orphan*/  v4 ; 
 float v5 ; 
 float w0 ; 
 float w1 ; 
 float w2 ; 
 float w3 ; 
 float w4 ; 
 float w5 ; 
 float w6 ; 

float __lgammaf_r(float x, int *signgamp)
{
	union {float f; uint32_t i;} u = {x};
	float t,y,z,nadj,p,p1,p2,p3,q,r,w;
	uint32_t ix;
	int i,sign;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = u.i>>31;
	ix = u.i & 0x7fffffff;
	if (ix >= 0x7f800000)
		return x*x;
	if (ix < 0x35000000) {  /* |x| < 2**-21, return -log(|x|) */
		if (sign) {
			*signgamp = -1;
			x = -x;
		}
		return -logf(x);
	}
	if (sign) {
		x = -x;
		t = sin_pi(x);
		if (t == 0.0f) /* -integer */
			return 1.0f/(x-x);
		if (t > 0.0f)
			*signgamp = -1;
		else
			t = -t;
		nadj = logf(pi/(t*x));
	}

	/* purge off 1 and 2 */
	if (ix == 0x3f800000 || ix == 0x40000000)
		r = 0;
	/* for x < 2.0 */
	else if (ix < 0x40000000) {
		if (ix <= 0x3f666666) {  /* lgamma(x) = lgamma(x+1)-log(x) */
			r = -logf(x);
			if (ix >= 0x3f3b4a20) {
				y = 1.0f - x;
				i = 0;
			} else if (ix >= 0x3e6d3308) {
				y = x - (tc-1.0f);
				i = 1;
			} else {
				y = x;
				i = 2;
			}
		} else {
			r = 0.0f;
			if (ix >= 0x3fdda618) {  /* [1.7316,2] */
				y = 2.0f - x;
				i = 0;
			} else if (ix >= 0x3F9da620) {  /* [1.23,1.73] */
				y = x - tc;
				i = 1;
			} else {
				y = x - 1.0f;
				i = 2;
			}
		}
		switch(i) {
		case 0:
			z = y*y;
			p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*a10))));
			p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*a11)))));
			p = y*p1+p2;
			r += p - 0.5f*y;
			break;
		case 1:
			z = y*y;
			w = z*y;
			p1 = t0+w*(t3+w*(t6+w*(t9 +w*t12)));    /* parallel comp */
			p2 = t1+w*(t4+w*(t7+w*(t10+w*t13)));
			p3 = t2+w*(t5+w*(t8+w*(t11+w*t14)));
			p = z*p1-(tt-w*(p2+y*p3));
			r += (tf + p);
			break;
		case 2:
			p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*u5)))));
			p2 = 1.0f+y*(v1+y*(v2+y*(v3+y*(v4+y*v5))));
			r += -0.5f*y + p1/p2;
		}
	} else if (ix < 0x41000000) {  /* x < 8.0 */
		i = (int)x;
		y = x - (float)i;
		p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
		q = 1.0f+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*r6)))));
		r = 0.5f*y+p/q;
		z = 1.0f;    /* lgamma(1+s) = log(s) + lgamma(s) */
		switch (i) {
		case 7: z *= y + 6.0f;  /* FALLTHRU */
		case 6: z *= y + 5.0f;  /* FALLTHRU */
		case 5: z *= y + 4.0f;  /* FALLTHRU */
		case 4: z *= y + 3.0f;  /* FALLTHRU */
		case 3: z *= y + 2.0f;  /* FALLTHRU */
			r += logf(z);
			break;
		}
	} else if (ix < 0x5c800000) {  /* 8.0 <= x < 2**58 */
		t = logf(x);
		z = 1.0f/x;
		y = z*z;
		w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*w6)))));
		r = (x-0.5f)*(t-1.0f)+w;
	} else                         /* 2**58 <= x <= inf */
		r =  x*(logf(x)-1.0f);
	if (sign)
		r = nadj - r;
	return r;
}