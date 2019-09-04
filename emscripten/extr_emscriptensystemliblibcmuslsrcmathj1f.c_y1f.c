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
 float* U0 ; 
 float* V0 ; 
 float common (int,float,int,int /*<<< orphan*/ ) ; 
 float j1f (float) ; 
 float logf (float) ; 
 float tpi ; 

float y1f(float x)
{
	float z,u,v;
	uint32_t ix;

	GET_FLOAT_WORD(ix, x);
	if ((ix & 0x7fffffff) == 0)
		return -1/0.0f;
	if (ix>>31)
		return 0/0.0f;
	if (ix >= 0x7f800000)
		return 1/x;
	if (ix >= 0x40000000)  /* |x| >= 2.0 */
		return common(ix,x,1,0);
	if (ix < 0x32000000)  /* x < 2**-27 */
		return -tpi/x;
	z = x*x;
	u = U0[0]+z*(U0[1]+z*(U0[2]+z*(U0[3]+z*U0[4])));
	v = 1.0f+z*(V0[0]+z*(V0[1]+z*(V0[2]+z*(V0[3]+z*V0[4]))));
	return x*(u/v) + tpi*(j1f(x)*logf(x)-1.0f/x);
}