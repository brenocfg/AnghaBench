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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  cond_negate (int*,size_t,int) ; 

__attribute__((used)) static uint32_t
co_reduce(uint16_t *a, uint16_t *b, size_t len,
	int32_t pa, int32_t pb, int32_t qa, int32_t qb)
{
	size_t k;
	int32_t cca, ccb;
	uint32_t nega, negb;

	cca = 0;
	ccb = 0;
	for (k = 0; k < len; k ++) {
		uint32_t wa, wb, za, zb;
		uint16_t tta, ttb;

		/*
		 * Since:
		 *   |pa| <= 2^15
		 *   |pb| <= 2^15
		 *   0 <= wa <= 2^15 - 1
		 *   0 <= wb <= 2^15 - 1
		 *   |cca| <= 2^16 - 1
		 * Then:
		 *   |za| <= (2^15-1)*(2^16) + (2^16-1) = 2^31 - 1
		 *
		 * Thus, the new value of cca is such that |cca| <= 2^16 - 1.
		 * The same applies to ccb.
		 */
		wa = a[k];
		wb = b[k];
		za = wa * (uint32_t)pa + wb * (uint32_t)pb + (uint32_t)cca;
		zb = wa * (uint32_t)qa + wb * (uint32_t)qb + (uint32_t)ccb;
		if (k > 0) {
			a[k - 1] = za & 0x7FFF;
			b[k - 1] = zb & 0x7FFF;
		}
		tta = za >> 15;
		ttb = zb >> 15;
		cca = *(int16_t *)&tta;
		ccb = *(int16_t *)&ttb;
	}
	a[len - 1] = (uint16_t)cca;
	b[len - 1] = (uint16_t)ccb;
	nega = (uint32_t)cca >> 31;
	negb = (uint32_t)ccb >> 31;
	cond_negate(a, len, nega);
	cond_negate(b, len, negb);
	return nega | (negb << 1);
}