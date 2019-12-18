#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int* z; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int,TYPE_1__*,TYPE_1__*,int) ; 
 int EQ (int,int /*<<< orphan*/ ) ; 
 int p256_add (TYPE_1__*,TYPE_1__*) ; 
 int p256_decode (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  p256_double (TYPE_1__*) ; 
 int /*<<< orphan*/  p256_encode (unsigned char*,TYPE_1__*) ; 
 int /*<<< orphan*/  p256_mul (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  p256_mulgen (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  p256_to_affine (TYPE_1__*) ; 
 int /*<<< orphan*/  reduce_final_f256 (int*) ; 

__attribute__((used)) static uint32_t
api_muladd(unsigned char *A, const unsigned char *B, size_t len,
	const unsigned char *x, size_t xlen,
	const unsigned char *y, size_t ylen, int curve)
{
	p256_jacobian P, Q;
	uint32_t r, t, z;
	int i;

	(void)curve;
	r = p256_decode(&P, A, len);
	p256_mul(&P, x, xlen);
	if (B == NULL) {
		p256_mulgen(&Q, y, ylen);
	} else {
		r &= p256_decode(&Q, B, len);
		p256_mul(&Q, y, ylen);
	}

	/*
	 * The final addition may fail in case both points are equal.
	 */
	t = p256_add(&P, &Q);
	reduce_final_f256(P.z);
	z = 0;
	for (i = 0; i < 20; i ++) {
		z |= P.z[i];
	}
	z = EQ(z, 0);
	p256_double(&Q);

	/*
	 * If z is 1 then either P+Q = 0 (t = 1) or P = Q (t = 0). So we
	 * have the following:
	 *
	 *   z = 0, t = 0   return P (normal addition)
	 *   z = 0, t = 1   return P (normal addition)
	 *   z = 1, t = 0   return Q (a 'double' case)
	 *   z = 1, t = 1   report an error (P+Q = 0)
	 */
	CCOPY(z & ~t, &P, &Q, sizeof Q);
	p256_to_affine(&P);
	p256_encode(A, &P);
	r &= ~(z & t);
	return r;
}