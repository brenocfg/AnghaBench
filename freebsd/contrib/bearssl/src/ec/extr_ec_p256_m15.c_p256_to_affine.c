#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * z; int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mul_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reduce_final_f256 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  square_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
p256_to_affine(p256_jacobian *P)
{
	uint32_t t1[20], t2[20];
	int i;

	/*
	 * Invert z with a modular exponentiation: the modulus is
	 * p = 2^256 - 2^224 + 2^192 + 2^96 - 1, and the exponent is
	 * p-2. Exponent bit pattern (from high to low) is:
	 *  - 32 bits of value 1
	 *  - 31 bits of value 0
	 *  - 1 bit of value 1
	 *  - 96 bits of value 0
	 *  - 94 bits of value 1
	 *  - 1 bit of value 0
	 *  - 1 bit of value 1
	 * Thus, we precompute z^(2^31-1) to speed things up.
	 *
	 * If z = 0 (point at infinity) then the modular exponentiation
	 * will yield 0, which leads to the expected result (all three
	 * coordinates set to 0).
	 */

	/*
	 * A simple square-and-multiply for z^(2^31-1). We could save about
	 * two dozen multiplications here with an addition chain, but
	 * this would require a bit more code, and extra stack buffers.
	 */
	memcpy(t1, P->z, sizeof P->z);
	for (i = 0; i < 30; i ++) {
		square_f256(t1, t1);
		mul_f256(t1, t1, P->z);
	}

	/*
	 * Square-and-multiply. Apart from the squarings, we have a few
	 * multiplications to set bits to 1; we multiply by the original z
	 * for setting 1 bit, and by t1 for setting 31 bits.
	 */
	memcpy(t2, P->z, sizeof P->z);
	for (i = 1; i < 256; i ++) {
		square_f256(t2, t2);
		switch (i) {
		case 31:
		case 190:
		case 221:
		case 252:
			mul_f256(t2, t2, t1);
			break;
		case 63:
		case 253:
		case 255:
			mul_f256(t2, t2, P->z);
			break;
		}
	}

	/*
	 * Now that we have 1/z, multiply x by 1/z^2 and y by 1/z^3.
	 */
	mul_f256(t1, t2, t2);
	mul_f256(P->x, t1, P->x);
	mul_f256(t1, t1, t2);
	mul_f256(P->y, t1, P->y);
	reduce_final_f256(P->x);
	reduce_final_f256(P->y);

	/*
	 * Multiply z by 1/z. If z = 0, then this will yield 0, otherwise
	 * this will set z to 1.
	 */
	mul_f256(P->z, P->z, t2);
	reduce_final_f256(P->z);
}