#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rng_tfm {int /*<<< orphan*/  rng_reset; int /*<<< orphan*/  rng_gen_random; } ;
struct rng_alg {int /*<<< orphan*/  rng_make_random; } ;
struct crypto_tfm {struct rng_tfm crt_rng; TYPE_1__* __crt_alg; } ;
struct TYPE_2__ {struct rng_alg cra_rng; } ;

/* Variables and functions */
 int /*<<< orphan*/  rngapi_reset ; 

__attribute__((used)) static int crypto_init_rng_ops(struct crypto_tfm *tfm, u32 type, u32 mask)
{
	struct rng_alg *alg = &tfm->__crt_alg->cra_rng;
	struct rng_tfm *ops = &tfm->crt_rng;

	ops->rng_gen_random = alg->rng_make_random;
	ops->rng_reset = rngapi_reset;

	return 0;
}