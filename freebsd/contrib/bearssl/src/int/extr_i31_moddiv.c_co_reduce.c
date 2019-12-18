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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int M ; 
 int /*<<< orphan*/  cond_negate (int*,size_t,int) ; 

__attribute__((used)) static uint32_t
co_reduce(uint32_t *a, uint32_t *b, size_t len,
	int64_t pa, int64_t pb, int64_t qa, int64_t qb)
{
	size_t k;
	int64_t cca, ccb;
	uint32_t nega, negb;

	cca = 0;
	ccb = 0;
	for (k = 0; k < len; k ++) {
		uint32_t wa, wb;
		uint64_t za, zb;
		uint64_t tta, ttb;

		/*
		 * Since:
		 *   |pa| <= 2^31
		 *   |pb| <= 2^31
		 *   0 <= wa <= 2^31 - 1
		 *   0 <= wb <= 2^31 - 1
		 *   |cca| <= 2^32 - 1
		 * Then:
		 *   |za| <= (2^31-1)*(2^32) + (2^32-1) = 2^63 - 1
		 *
		 * Thus, the new value of cca is such that |cca| <= 2^32 - 1.
		 * The same applies to ccb.
		 */
		wa = a[k];
		wb = b[k];
		za = wa * (uint64_t)pa + wb * (uint64_t)pb + (uint64_t)cca;
		zb = wa * (uint64_t)qa + wb * (uint64_t)qb + (uint64_t)ccb;
		if (k > 0) {
			a[k - 1] = za & 0x7FFFFFFF;
			b[k - 1] = zb & 0x7FFFFFFF;
		}

		/*
		 * For the new values of cca and ccb, we need a signed
		 * right-shift; since, in C, right-shifting a signed
		 * negative value is implementation-defined, we use a
		 * custom portable sign extension expression.
		 */
#define M   ((uint64_t)1 << 32)
		tta = za >> 31;
		ttb = zb >> 31;
		tta = (tta ^ M) - M;
		ttb = (ttb ^ M) - M;
		cca = *(int64_t *)&tta;
		ccb = *(int64_t *)&ttb;
#undef M
	}
	a[len - 1] = (uint32_t)cca;
	b[len - 1] = (uint32_t)ccb;

	nega = (uint32_t)((uint64_t)cca >> 63);
	negb = (uint32_t)((uint64_t)ccb >> 63);
	cond_negate(a, len, nega);
	cond_negate(b, len, negb);
	return nega | (negb << 1);
}