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
struct TYPE_6__ {int initialized; int idx; TYPE_1__* sfmt; } ;
typedef  TYPE_2__ sfmt_t ;
struct TYPE_5__ {int* u; } ;

/* Variables and functions */
 int N32 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_rand_all (TYPE_2__*) ; 

uint64_t gen_rand64(sfmt_t *ctx) {
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    uint32_t r1, r2;
    uint32_t *psfmt32 = &ctx->sfmt[0].u[0];
#else
    uint64_t r;
    uint64_t *psfmt64 = (uint64_t *)&ctx->sfmt[0].u[0];
#endif

    assert(ctx->initialized);
    assert(ctx->idx % 2 == 0);

    if (ctx->idx >= N32) {
	gen_rand_all(ctx);
	ctx->idx = 0;
    }
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    r1 = psfmt32[ctx->idx];
    r2 = psfmt32[ctx->idx + 1];
    ctx->idx += 2;
    return ((uint64_t)r2 << 32) | r1;
#else
    r = psfmt64[ctx->idx / 2];
    ctx->idx += 2;
    return r;
#endif
}