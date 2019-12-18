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
 int /*<<< orphan*/  norm13 (int*,int*,int) ; 

__attribute__((used)) static void
reduce_f256(uint32_t *d)
{
	uint32_t x;

	x = d[19] >> 9;
	d[19] &= 0x01FF;
	d[17] += x << 3;
	d[14] -= x << 10;
	d[7] -= x << 5;
	d[0] += x;
	norm13(d, d, 20);
}