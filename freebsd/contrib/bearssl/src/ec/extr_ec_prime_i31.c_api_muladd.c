#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/ * c; } ;
typedef  TYPE_1__ jacobian ;
typedef  int /*<<< orphan*/  curve_params ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int,TYPE_1__*,TYPE_1__*,int) ; 
 unsigned char* api_generator (int,size_t*) ; 
 int br_i31_iszero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * id_to_curve (int) ; 
 int point_add (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int point_decode (TYPE_1__*,unsigned char const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  point_double (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  point_encode (unsigned char*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  point_mul (TYPE_1__*,unsigned char const*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static uint32_t
api_muladd(unsigned char *A, const unsigned char *B, size_t len,
	const unsigned char *x, size_t xlen,
	const unsigned char *y, size_t ylen, int curve)
{
	uint32_t r, t, z;
	const curve_params *cc;
	jacobian P, Q;

	/*
	 * TODO: see about merging the two ladders. Right now, we do
	 * two independent point multiplications, which is a bit
	 * wasteful of CPU resources (but yields short code).
	 */

	cc = id_to_curve(curve);
	r = point_decode(&P, A, len, cc);
	if (B == NULL) {
		size_t Glen;

		B = api_generator(curve, &Glen);
	}
	r &= point_decode(&Q, B, len, cc);
	point_mul(&P, x, xlen, cc);
	point_mul(&Q, y, ylen, cc);

	/*
	 * We want to compute P+Q. Since the base points A and B are distinct
	 * from infinity, and the multipliers are non-zero and lower than the
	 * curve order, then we know that P and Q are non-infinity. This
	 * leaves two special situations to test for:
	 * -- If P = Q then we must use point_double().
	 * -- If P+Q = 0 then we must report an error.
	 */
	t = point_add(&P, &Q, cc);
	point_double(&Q, cc);
	z = br_i31_iszero(P.c[2]);

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
	point_encode(A, &P, cc);
	r &= ~(z & t);

	return r;
}