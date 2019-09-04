#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ idx; TYPE_1__* state; } ;
typedef  TYPE_2__ sfmt_t ;
struct TYPE_5__ {int /*<<< orphan*/ * u; } ;

/* Variables and functions */
 scalar_t__ SFMT_N32 ; 
 int /*<<< orphan*/  sfmt_gen_rand_all (TYPE_2__*) ; 

__attribute__((used)) inline static uint32_t sfmt_genrand_uint32(sfmt_t * sfmt) {
    uint32_t r;
    uint32_t * psfmt32 = &sfmt->state[0].u[0];

    if (sfmt->idx >= SFMT_N32) {
	sfmt_gen_rand_all(sfmt);
	sfmt->idx = 0;
    }
    r = psfmt32[sfmt->idx++];
    return r;
}