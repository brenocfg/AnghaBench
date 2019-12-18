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

__attribute__((used)) static __inline__ unsigned int
idt77252_fls(unsigned int x)
{
	int r = 1;

	if (x == 0)
		return 0;
	if (x & 0xffff0000) {
		x >>= 16;
		r += 16;
	}
	if (x & 0xff00) {
		x >>= 8;
		r += 8;
	}
	if (x & 0xf0) {
		x >>= 4;
		r += 4;
	}
	if (x & 0xc) {
		x >>= 2;
		r += 2;
	}
	if (x & 0x2)
		r += 1;
	return r;
}