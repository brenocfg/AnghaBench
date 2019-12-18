#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* z; int* x; int* y; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  mul_f256 (int*,int*,int*) ; 
 int /*<<< orphan*/  reduce_final_f256 (int*) ; 
 int /*<<< orphan*/  square_f256 (int*,int*) ; 
 int /*<<< orphan*/  sub_f256 (int*,int*,int*) ; 

__attribute__((used)) static uint32_t
p256_add(p256_jacobian *P1, const p256_jacobian *P2)
{
	/*
	 * Addtions formulas are:
	 *
	 *   u1 = x1 * z2^2
	 *   u2 = x2 * z1^2
	 *   s1 = y1 * z2^3
	 *   s2 = y2 * z1^3
	 *   h = u2 - u1
	 *   r = s2 - s1
	 *   x3 = r^2 - h^3 - 2 * u1 * h^2
	 *   y3 = r * (u1 * h^2 - x3) - s1 * h^3
	 *   z3 = h * z1 * z2
	 */
	uint32_t t1[9], t2[9], t3[9], t4[9], t5[9], t6[9], t7[9];
	uint32_t ret;
	int i;

	/*
	 * Compute u1 = x1*z2^2 (in t1) and s1 = y1*z2^3 (in t3).
	 */
	square_f256(t3, P2->z);
	mul_f256(t1, P1->x, t3);
	mul_f256(t4, P2->z, t3);
	mul_f256(t3, P1->y, t4);

	/*
	 * Compute u2 = x2*z1^2 (in t2) and s2 = y2*z1^3 (in t4).
	 */
	square_f256(t4, P1->z);
	mul_f256(t2, P2->x, t4);
	mul_f256(t5, P1->z, t4);
	mul_f256(t4, P2->y, t5);

	/*
	 * Compute h = h2 - u1 (in t2) and r = s2 - s1 (in t4).
	 * We need to test whether r is zero, so we will do some extra
	 * reduce.
	 */
	sub_f256(t2, t2, t1);
	sub_f256(t4, t4, t3);
	reduce_final_f256(t4);
	ret = 0;
	for (i = 0; i < 9; i ++) {
		ret |= t4[i];
	}
	ret = (ret | -ret) >> 31;

	/*
	 * Compute u1*h^2 (in t6) and h^3 (in t5);
	 */
	square_f256(t7, t2);
	mul_f256(t6, t1, t7);
	mul_f256(t5, t7, t2);

	/*
	 * Compute x3 = r^2 - h^3 - 2*u1*h^2.
	 */
	square_f256(P1->x, t4);
	sub_f256(P1->x, P1->x, t5);
	sub_f256(P1->x, P1->x, t6);
	sub_f256(P1->x, P1->x, t6);

	/*
	 * Compute y3 = r*(u1*h^2 - x3) - s1*h^3.
	 */
	sub_f256(t6, t6, P1->x);
	mul_f256(P1->y, t4, t6);
	mul_f256(t1, t5, t3);
	sub_f256(P1->y, P1->y, t1);

	/*
	 * Compute z3 = h*z1*z2.
	 */
	mul_f256(t1, P1->z, P2->z);
	mul_f256(P1->z, t1, t2);

	return ret;
}