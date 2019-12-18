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
typedef  int u64 ;
struct div_result {int result_high; int result_low; } ;

/* Variables and functions */
 scalar_t__ do_div (int,unsigned int) ; 

void div128_by_32(u64 dividend_high, u64 dividend_low,
		  unsigned divisor, struct div_result *dr)
{
	unsigned long a, b, c, d;
	unsigned long w, x, y, z;
	u64 ra, rb, rc;

	a = dividend_high >> 32;
	b = dividend_high & 0xffffffff;
	c = dividend_low >> 32;
	d = dividend_low & 0xffffffff;

	w = a / divisor;
	ra = ((u64)(a - (w * divisor)) << 32) + b;

	rb = ((u64) do_div(ra, divisor) << 32) + c;
	x = ra;

	rc = ((u64) do_div(rb, divisor) << 32) + d;
	y = rb;

	do_div(rc, divisor);
	z = rc;

	dr->result_high = ((u64)w << 32) + x;
	dr->result_low  = ((u64)y << 32) + z;

}