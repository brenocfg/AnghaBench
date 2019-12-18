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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int idx; TYPE_1__* state; } ;
typedef  TYPE_2__ sfmt_t ;
struct TYPE_5__ {int* u; int* u64; } ;

/* Variables and functions */
 int SFMT_N32 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sfmt_gen_rand_all (TYPE_2__*) ; 

__attribute__((used)) inline static uint64_t sfmt_genrand_uint64(sfmt_t * sfmt) {
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    uint32_t * psfmt32 = &sfmt->state[0].u[0];
    uint32_t r1, r2;
#else
    uint64_t r;
#endif
    uint64_t * psfmt64 = &sfmt->state[0].u64[0];
    assert(sfmt->idx % 2 == 0);

    if (sfmt->idx >= SFMT_N32) {
	sfmt_gen_rand_all(sfmt);
	sfmt->idx = 0;
    }
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    r1 = psfmt32[sfmt->idx];
    r2 = psfmt32[sfmt->idx + 1];
    sfmt->idx += 2;
    return ((uint64_t)r2 << 32) | r1;
#else
    r = psfmt64[sfmt->idx / 2];
    sfmt->idx += 2;
    return r;
#endif
}