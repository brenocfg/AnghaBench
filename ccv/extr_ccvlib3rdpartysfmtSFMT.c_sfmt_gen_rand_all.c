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
typedef  int /*<<< orphan*/  w128_t ;
struct TYPE_3__ {int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ sfmt_t ;

/* Variables and functions */
 int SFMT_N ; 
 int SFMT_POS1 ; 
 int /*<<< orphan*/  do_recursion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void sfmt_gen_rand_all(sfmt_t * sfmt) {
    int i;
    w128_t *r1, *r2;

    r1 = &sfmt->state[SFMT_N - 2];
    r2 = &sfmt->state[SFMT_N - 1];
    for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
	do_recursion(&sfmt->state[i], &sfmt->state[i],
		     &sfmt->state[i + SFMT_POS1], r1, r2);
	r1 = r2;
	r2 = &sfmt->state[i];
    }
    for (; i < SFMT_N; i++) {
	do_recursion(&sfmt->state[i], &sfmt->state[i],
		     &sfmt->state[i + SFMT_POS1 - SFMT_N], r1, r2);
	r1 = r2;
	r2 = &sfmt->state[i];
    }
}