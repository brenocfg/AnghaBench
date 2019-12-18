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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static u32 exnor(u32 a,u32 b)
{
	u32 c,d,e,f,r1,r2,r3,r4;

	c = 0;
	while(c<b) {
		d = (a<<23);
		e = (a<<15);
		f = (a<<7);
		r1 = (a^f);
		r2 = (e^r1);
		r3 = ~(d^r2);		//eqv(d,r2)
		e = (a<<1);
		r4 = ((r3>>30)&0x02);
		a = (e|r4);
		c++;
	};
	return a;
}