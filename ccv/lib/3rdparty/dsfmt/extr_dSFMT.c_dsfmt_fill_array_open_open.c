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
typedef  int /*<<< orphan*/  dw128_t ;
typedef  int /*<<< orphan*/  dsfmt_t ;

/* Variables and functions */
 int DSFMT_N64 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_rand_array_o0o1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void dsfmt_fill_array_open_open(dsfmt_t *dsfmt, double array[], int size) {
    assert(size % 2 == 0);
    assert(size >= DSFMT_N64);
    gen_rand_array_o0o1(dsfmt, (dw128_t *)array, size / 2);
}