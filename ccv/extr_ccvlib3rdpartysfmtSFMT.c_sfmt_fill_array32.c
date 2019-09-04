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
typedef  int /*<<< orphan*/  w128_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int idx; } ;
typedef  TYPE_1__ sfmt_t ;

/* Variables and functions */
 int SFMT_N32 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_rand_array (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void sfmt_fill_array32(sfmt_t * sfmt, uint32_t *array, int size) {
    assert(sfmt->idx == SFMT_N32);
    assert(size % 4 == 0);
    assert(size >= SFMT_N32);

    gen_rand_array(sfmt, (w128_t *)array, size / 4);
    sfmt->idx = SFMT_N32;
}