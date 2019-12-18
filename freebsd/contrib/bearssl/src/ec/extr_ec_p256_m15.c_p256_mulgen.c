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
typedef  int /*<<< orphan*/  p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int NEQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_Gwin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p256_add_mixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p256_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
p256_mulgen(p256_jacobian *P, const unsigned char *x, size_t xlen)
{
	/*
	 * qz is a flag that is initially 1, and remains equal to 1
	 * as long as the point is the point at infinity.
	 *
	 * We use a 4-bit window to handle multiplier bits by groups
	 * of 4. The precomputed window is constant static data, with
	 * points in affine coordinates; we use a constant-time lookup.
	 */
	p256_jacobian Q;
	uint32_t qz;

	memset(&Q, 0, sizeof Q);
	qz = 1;
	while (xlen -- > 0) {
		int k;
		unsigned bx;

		bx = *x ++;
		for (k = 0; k < 2; k ++) {
			uint32_t bits;
			uint32_t bnz;
			p256_jacobian T, U;

			p256_double(&Q);
			p256_double(&Q);
			p256_double(&Q);
			p256_double(&Q);
			bits = (bx >> 4) & 0x0F;
			bnz = NEQ(bits, 0);
			lookup_Gwin(&T, bits);
			U = Q;
			p256_add_mixed(&U, &T);
			CCOPY(bnz & qz, &Q, &T, sizeof Q);
			CCOPY(bnz & ~qz, &Q, &U, sizeof Q);
			qz &= ~bnz;
			bx <<= 4;
		}
	}
	*P = Q;
}