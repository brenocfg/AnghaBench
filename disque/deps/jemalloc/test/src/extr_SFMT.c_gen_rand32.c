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
struct TYPE_6__ {scalar_t__ idx; int /*<<< orphan*/  initialized; TYPE_1__* sfmt; } ;
typedef  TYPE_2__ sfmt_t ;
struct TYPE_5__ {int /*<<< orphan*/ * u; } ;

/* Variables and functions */
 scalar_t__ N32 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rand_all (TYPE_2__*) ; 

uint32_t gen_rand32(sfmt_t *ctx) {
    uint32_t r;
    uint32_t *psfmt32 = &ctx->sfmt[0].u[0];

    assert(ctx->initialized);
    if (ctx->idx >= N32) {
	gen_rand_all(ctx);
	ctx->idx = 0;
    }
    r = psfmt32[ctx->idx++];
    return r;
}