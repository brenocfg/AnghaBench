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
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 float y0f (float) ; 
 float y1f (float) ; 

float ynf(int n, float x)
{
	uint32_t ix, ib;
	int nm1, sign, i;
	float a, b, temp;

	GET_FLOAT_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix > 0x7f800000) /* nan */
		return x;
	if (sign && ix != 0) /* x < 0 */
		return 0/0.0f;
	if (ix == 0x7f800000)
		return 0.0f;

	if (n == 0)
		return y0f(x);
	if (n < 0) {
		nm1 = -(n+1);
		sign = n&1;
	} else {
		nm1 = n-1;
		sign = 0;
	}
	if (nm1 == 0)
		return sign ? -y1f(x) : y1f(x);

	a = y0f(x);
	b = y1f(x);
	/* quit if b is -inf */
	GET_FLOAT_WORD(ib,b);
	for (i = 0; i < nm1 && ib != 0xff800000; ) {
		i++;
		temp = b;
		b = (2.0f*i/x)*b - a;
		GET_FLOAT_WORD(ib, b);
		a = temp;
	}
	return sign ? -b : b;
}