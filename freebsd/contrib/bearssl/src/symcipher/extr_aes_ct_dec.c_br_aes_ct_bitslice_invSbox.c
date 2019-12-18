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
 int /*<<< orphan*/  br_aes_ct_bitslice_Sbox (int*) ; 

void
br_aes_ct_bitslice_invSbox(uint32_t *q)
{
	/*
	 * AES S-box is:
	 *   S(x) = A(I(x)) ^ 0x63
	 * where I() is inversion in GF(256), and A() is a linear
	 * transform (0 is formally defined to be its own inverse).
	 * Since inversion is an involution, the inverse S-box can be
	 * computed from the S-box as:
	 *   iS(x) = B(S(B(x ^ 0x63)) ^ 0x63)
	 * where B() is the inverse of A(). Indeed, for any y in GF(256):
	 *   iS(S(y)) = B(A(I(B(A(I(y)) ^ 0x63 ^ 0x63))) ^ 0x63 ^ 0x63) = y
	 *
	 * Note: we reuse the implementation of the forward S-box,
	 * instead of duplicating it here, so that total code size is
	 * lower. By merging the B() transforms into the S-box circuit
	 * we could make faster CBC decryption, but CBC decryption is
	 * already quite faster than CBC encryption because we can
	 * process two blocks in parallel.
	 */
	uint32_t q0, q1, q2, q3, q4, q5, q6, q7;

	q0 = ~q[0];
	q1 = ~q[1];
	q2 = q[2];
	q3 = q[3];
	q4 = q[4];
	q5 = ~q[5];
	q6 = ~q[6];
	q7 = q[7];
	q[7] = q1 ^ q4 ^ q6;
	q[6] = q0 ^ q3 ^ q5;
	q[5] = q7 ^ q2 ^ q4;
	q[4] = q6 ^ q1 ^ q3;
	q[3] = q5 ^ q0 ^ q2;
	q[2] = q4 ^ q7 ^ q1;
	q[1] = q3 ^ q6 ^ q0;
	q[0] = q2 ^ q5 ^ q7;

	br_aes_ct_bitslice_Sbox(q);

	q0 = ~q[0];
	q1 = ~q[1];
	q2 = q[2];
	q3 = q[3];
	q4 = q[4];
	q5 = ~q[5];
	q6 = ~q[6];
	q7 = q[7];
	q[7] = q1 ^ q4 ^ q6;
	q[6] = q0 ^ q3 ^ q5;
	q[5] = q7 ^ q2 ^ q4;
	q[4] = q6 ^ q1 ^ q3;
	q[3] = q5 ^ q0 ^ q2;
	q[2] = q4 ^ q7 ^ q1;
	q[1] = q3 ^ q6 ^ q0;
	q[0] = q2 ^ q5 ^ q7;
}