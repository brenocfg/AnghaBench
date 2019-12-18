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
struct TYPE_4__ {int* x; int* y; int* z; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int* F256 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mul_f256 (int*,int*,int*) ; 
 int /*<<< orphan*/  norm13 (int*,int*,int) ; 
 int /*<<< orphan*/  reduce_f256 (int*) ; 
 int /*<<< orphan*/  reduce_final_f256 (int*) ; 
 int /*<<< orphan*/  square_f256 (int*,int*) ; 

__attribute__((used)) static uint32_t
p256_add_mixed(p256_jacobian *P1, const p256_jacobian *P2)
{
	/*
	 * Addtions formulas are:
	 *
	 *   u1 = x1
	 *   u2 = x2 * z1^2
	 *   s1 = y1
	 *   s2 = y2 * z1^3
	 *   h = u2 - u1
	 *   r = s2 - s1
	 *   x3 = r^2 - h^3 - 2 * u1 * h^2
	 *   y3 = r * (u1 * h^2 - x3) - s1 * h^3
	 *   z3 = h * z1
	 */
	uint32_t t1[20], t2[20], t3[20], t4[20], t5[20], t6[20], t7[20];
	uint32_t ret;
	int i;

	/*
	 * Compute u1 = x1 (in t1) and s1 = y1 (in t3).
	 */
	memcpy(t1, P1->x, sizeof t1);
	memcpy(t3, P1->y, sizeof t3);

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
	for (i = 0; i < 20; i ++) {
		t2[i] += (F256[i] << 1) - t1[i];
		t4[i] += (F256[i] << 1) - t3[i];
	}
	norm13(t2, t2, 20);
	norm13(t4, t4, 20);
	reduce_f256(t4);
	reduce_final_f256(t4);
	ret = 0;
	for (i = 0; i < 20; i ++) {
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
	for (i = 0; i < 20; i ++) {
		P1->x[i] += (F256[i] << 3) - t5[i] - (t6[i] << 1);
	}
	norm13(P1->x, P1->x, 20);
	reduce_f256(P1->x);

	/*
	 * Compute y3 = r*(u1*h^2 - x3) - s1*h^3.
	 */
	for (i = 0; i < 20; i ++) {
		t6[i] += (F256[i] << 1) - P1->x[i];
	}
	norm13(t6, t6, 20);
	mul_f256(P1->y, t4, t6);
	mul_f256(t1, t5, t3);
	for (i = 0; i < 20; i ++) {
		P1->y[i] += (F256[i] << 1) - t1[i];
	}
	norm13(P1->y, P1->y, 20);
	reduce_f256(P1->y);

	/*
	 * Compute z3 = h*z1*z2.
	 */
	mul_f256(P1->z, P1->z, t2);

	return ret;
}