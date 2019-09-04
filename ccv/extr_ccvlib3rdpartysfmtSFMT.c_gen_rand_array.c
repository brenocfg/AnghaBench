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
typedef  void* w128_t ;
struct TYPE_3__ {void** state; } ;
typedef  TYPE_1__ sfmt_t ;

/* Variables and functions */
 int SFMT_N ; 
 int SFMT_POS1 ; 
 int /*<<< orphan*/  do_recursion (void**,void**,void**,void**,void**) ; 

__attribute__((used)) inline static void gen_rand_array(sfmt_t * sfmt, w128_t *array, int size) {
    int i, j;
    w128_t *r1, *r2;

    r1 = &sfmt->state[SFMT_N - 2];
    r2 = &sfmt->state[SFMT_N - 1];
    for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
	do_recursion(&array[i], &sfmt->state[i], &sfmt->state[i + SFMT_POS1], r1, r2);
	r1 = r2;
	r2 = &array[i];
    }
    for (; i < SFMT_N; i++) {
	do_recursion(&array[i], &sfmt->state[i],
		     &array[i + SFMT_POS1 - SFMT_N], r1, r2);
	r1 = r2;
	r2 = &array[i];
    }
    for (; i < size - SFMT_N; i++) {
	do_recursion(&array[i], &array[i - SFMT_N],
		     &array[i + SFMT_POS1 - SFMT_N], r1, r2);
	r1 = r2;
	r2 = &array[i];
    }
    for (j = 0; j < 2 * SFMT_N - size; j++) {
	sfmt->state[j] = array[j + size - SFMT_N];
    }
    for (; i < size; i++, j++) {
	do_recursion(&array[i], &array[i - SFMT_N],
		     &array[i + SFMT_POS1 - SFMT_N], r1, r2);
	r1 = r2;
	r2 = &array[i];
	sfmt->state[j] = array[i];
    }
}