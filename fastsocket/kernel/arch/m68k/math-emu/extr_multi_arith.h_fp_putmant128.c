#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union fp_mant128 {int* m32; int /*<<< orphan*/ * m64; } ;
struct TYPE_2__ {int* m32; int /*<<< orphan*/  m64; } ;
struct fp_ext {int lowmant; TYPE_1__ mant; } ;

/* Variables and functions */

__attribute__((used)) static inline void fp_putmant128(struct fp_ext *dest, union fp_mant128 *src,
				 int shift)
{
	unsigned long tmp;

	switch (shift) {
	case 0:
		dest->mant.m64 = src->m64[0];
		dest->lowmant = src->m32[2] >> 24;
		if (src->m32[3] || (src->m32[2] << 8))
			dest->lowmant |= 1;
		break;
	case 1:
		asm volatile ("lsl.l #1,%0"
			: "=d" (tmp) : "0" (src->m32[2]));
		asm volatile ("roxl.l #1,%0"
			: "=d" (dest->mant.m32[1]) : "0" (src->m32[1]));
		asm volatile ("roxl.l #1,%0"
			: "=d" (dest->mant.m32[0]) : "0" (src->m32[0]));
		dest->lowmant = tmp >> 24;
		if (src->m32[3] || (tmp << 8))
			dest->lowmant |= 1;
		break;
	case 31:
		asm volatile ("lsr.l #1,%1; roxr.l #1,%0"
			: "=d" (dest->mant.m32[0])
			: "d" (src->m32[0]), "0" (src->m32[1]));
		asm volatile ("roxr.l #1,%0"
			: "=d" (dest->mant.m32[1]) : "0" (src->m32[2]));
		asm volatile ("roxr.l #1,%0"
			: "=d" (tmp) : "0" (src->m32[3]));
		dest->lowmant = tmp >> 24;
		if (src->m32[3] << 7)
			dest->lowmant |= 1;
		break;
	case 32:
		dest->mant.m32[0] = src->m32[1];
		dest->mant.m32[1] = src->m32[2];
		dest->lowmant = src->m32[3] >> 24;
		if (src->m32[3] << 8)
			dest->lowmant |= 1;
		break;
	}
}