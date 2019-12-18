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
 int rotr16 (int) ; 

__attribute__((used)) static void
inv_mix_columns(uint32_t *q)
{
	uint32_t q0, q1, q2, q3, q4, q5, q6, q7;
	uint32_t r0, r1, r2, r3, r4, r5, r6, r7;

	q0 = q[0];
	q1 = q[1];
	q2 = q[2];
	q3 = q[3];
	q4 = q[4];
	q5 = q[5];
	q6 = q[6];
	q7 = q[7];
	r0 = (q0 >> 8) | (q0 << 24);
	r1 = (q1 >> 8) | (q1 << 24);
	r2 = (q2 >> 8) | (q2 << 24);
	r3 = (q3 >> 8) | (q3 << 24);
	r4 = (q4 >> 8) | (q4 << 24);
	r5 = (q5 >> 8) | (q5 << 24);
	r6 = (q6 >> 8) | (q6 << 24);
	r7 = (q7 >> 8) | (q7 << 24);

	q[0] = q5 ^ q6 ^ q7 ^ r0 ^ r5 ^ r7 ^ rotr16(q0 ^ q5 ^ q6 ^ r0 ^ r5);
	q[1] = q0 ^ q5 ^ r0 ^ r1 ^ r5 ^ r6 ^ r7 ^ rotr16(q1 ^ q5 ^ q7 ^ r1 ^ r5 ^ r6);
	q[2] = q0 ^ q1 ^ q6 ^ r1 ^ r2 ^ r6 ^ r7 ^ rotr16(q0 ^ q2 ^ q6 ^ r2 ^ r6 ^ r7);
	q[3] = q0 ^ q1 ^ q2 ^ q5 ^ q6 ^ r0 ^ r2 ^ r3 ^ r5 ^ rotr16(q0 ^ q1 ^ q3 ^ q5 ^ q6 ^ q7 ^ r0 ^ r3 ^ r5 ^ r7);
	q[4] = q1 ^ q2 ^ q3 ^ q5 ^ r1 ^ r3 ^ r4 ^ r5 ^ r6 ^ r7 ^ rotr16(q1 ^ q2 ^ q4 ^ q5 ^ q7 ^ r1 ^ r4 ^ r5 ^ r6);
	q[5] = q2 ^ q3 ^ q4 ^ q6 ^ r2 ^ r4 ^ r5 ^ r6 ^ r7 ^ rotr16(q2 ^ q3 ^ q5 ^ q6 ^ r2 ^ r5 ^ r6 ^ r7);
	q[6] = q3 ^ q4 ^ q5 ^ q7 ^ r3 ^ r5 ^ r6 ^ r7 ^ rotr16(q3 ^ q4 ^ q6 ^ q7 ^ r3 ^ r6 ^ r7);
	q[7] = q4 ^ q5 ^ q6 ^ r4 ^ r6 ^ r7 ^ rotr16(q4 ^ q5 ^ q7 ^ r4 ^ r7);
}