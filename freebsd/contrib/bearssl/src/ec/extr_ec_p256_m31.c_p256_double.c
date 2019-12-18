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
struct TYPE_3__ {int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; int /*<<< orphan*/ * z; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  add_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mul_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  square_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sub_f256 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
p256_double(p256_jacobian *Q)
{
	/*
	 * Doubling formulas are:
	 *
	 *   s = 4*x*y^2
	 *   m = 3*(x + z^2)*(x - z^2)
	 *   x' = m^2 - 2*s
	 *   y' = m*(s - x') - 8*y^4
	 *   z' = 2*y*z
	 *
	 * These formulas work for all points, including points of order 2
	 * and points at infinity:
	 *   - If y = 0 then z' = 0. But there is no such point in P-256
	 *     anyway.
	 *   - If z = 0 then z' = 0.
	 */
	uint32_t t1[9], t2[9], t3[9], t4[9];

	/*
	 * Compute z^2 in t1.
	 */
	square_f256(t1, Q->z);

	/*
	 * Compute x-z^2 in t2 and x+z^2 in t1.
	 */
	add_f256(t2, Q->x, t1);
	sub_f256(t1, Q->x, t1);

	/*
	 * Compute 3*(x+z^2)*(x-z^2) in t1.
	 */
	mul_f256(t3, t1, t2);
	add_f256(t1, t3, t3);
	add_f256(t1, t3, t1);

	/*
	 * Compute 4*x*y^2 (in t2) and 2*y^2 (in t3).
	 */
	square_f256(t3, Q->y);
	add_f256(t3, t3, t3);
	mul_f256(t2, Q->x, t3);
	add_f256(t2, t2, t2);

	/*
	 * Compute x' = m^2 - 2*s.
	 */
	square_f256(Q->x, t1);
	sub_f256(Q->x, Q->x, t2);
	sub_f256(Q->x, Q->x, t2);

	/*
	 * Compute z' = 2*y*z.
	 */
	mul_f256(t4, Q->y, Q->z);
	add_f256(Q->z, t4, t4);

	/*
	 * Compute y' = m*(s - x') - 8*y^4. Note that we already have
	 * 2*y^2 in t3.
	 */
	sub_f256(t2, t2, Q->x);
	mul_f256(Q->y, t1, t2);
	square_f256(t4, t3);
	add_f256(t4, t4, t4);
	sub_f256(Q->y, Q->y, t4);
}