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
typedef  int uint64_t ;

/* Variables and functions */
 int rotr32 (int) ; 

__attribute__((used)) static inline void
mix_columns(uint64_t *q)
{
	uint64_t q0, q1, q2, q3, q4, q5, q6, q7;
	uint64_t r0, r1, r2, r3, r4, r5, r6, r7;

	q0 = q[0];
	q1 = q[1];
	q2 = q[2];
	q3 = q[3];
	q4 = q[4];
	q5 = q[5];
	q6 = q[6];
	q7 = q[7];
	r0 = (q0 >> 16) | (q0 << 48);
	r1 = (q1 >> 16) | (q1 << 48);
	r2 = (q2 >> 16) | (q2 << 48);
	r3 = (q3 >> 16) | (q3 << 48);
	r4 = (q4 >> 16) | (q4 << 48);
	r5 = (q5 >> 16) | (q5 << 48);
	r6 = (q6 >> 16) | (q6 << 48);
	r7 = (q7 >> 16) | (q7 << 48);

	q[0] = q7 ^ r7 ^ r0 ^ rotr32(q0 ^ r0);
	q[1] = q0 ^ r0 ^ q7 ^ r7 ^ r1 ^ rotr32(q1 ^ r1);
	q[2] = q1 ^ r1 ^ r2 ^ rotr32(q2 ^ r2);
	q[3] = q2 ^ r2 ^ q7 ^ r7 ^ r3 ^ rotr32(q3 ^ r3);
	q[4] = q3 ^ r3 ^ q7 ^ r7 ^ r4 ^ rotr32(q4 ^ r4);
	q[5] = q4 ^ r4 ^ r5 ^ rotr32(q5 ^ r5);
	q[6] = q5 ^ r5 ^ r6 ^ rotr32(q6 ^ r6);
	q[7] = q6 ^ r6 ^ r7 ^ rotr32(q7 ^ r7);
}