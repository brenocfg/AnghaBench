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
typedef  int uint16_t ;
typedef  int int32_t ;

/* Variables and functions */
 int M ; 
 int /*<<< orphan*/  finish_mod (int*,size_t,int const*,int) ; 

__attribute__((used)) static void
co_reduce_mod(uint16_t *a, uint16_t *b, size_t len,
	int32_t pa, int32_t pb, int32_t qa, int32_t qb,
	const uint16_t *m, uint16_t m0i)
{
	size_t k;
	int32_t cca, ccb, fa, fb;

	cca = 0;
	ccb = 0;
	fa = ((a[0] * (uint32_t)pa + b[0] * (uint32_t)pb) * m0i) & 0x7FFF;
	fb = ((a[0] * (uint32_t)qa + b[0] * (uint32_t)qb) * m0i) & 0x7FFF;
	for (k = 0; k < len; k ++) {
		uint32_t wa, wb, za, zb;
		uint32_t tta, ttb;

		/*
		 * In this loop, carries 'cca' and 'ccb' always fit on
		 * 17 bits (in absolute value).
		 */
		wa = a[k];
		wb = b[k];
		za = wa * (uint32_t)pa + wb * (uint32_t)pb
			+ m[k] * (uint32_t)fa + (uint32_t)cca;
		zb = wa * (uint32_t)qa + wb * (uint32_t)qb
			+ m[k] * (uint32_t)fb + (uint32_t)ccb;
		if (k > 0) {
			a[k - 1] = za & 0x7FFF;
			b[k - 1] = zb & 0x7FFF;
		}

		/*
		 * The XOR-and-sub construction below does an arithmetic
		 * right shift in a portable way (technically, right-shifting
		 * a negative signed value is implementation-defined in C).
		 */
#define M   ((uint32_t)1 << 16)
		tta = za >> 15;
		ttb = zb >> 15;
		tta = (tta ^ M) - M;
		ttb = (ttb ^ M) - M;
		cca = *(int32_t *)&tta;
		ccb = *(int32_t *)&ttb;
#undef M
	}
	a[len - 1] = (uint32_t)cca;
	b[len - 1] = (uint32_t)ccb;

	/*
	 * At this point:
	 *   -m <= a < 2*m
	 *   -m <= b < 2*m
	 * (this is a case of Montgomery reduction)
	 * The top word of 'a' and 'b' may have a 16-th bit set.
	 * We may have to add or subtract the modulus.
	 */
	finish_mod(a, len, m, (uint32_t)cca >> 31);
	finish_mod(b, len, m, (uint32_t)ccb >> 31);
}