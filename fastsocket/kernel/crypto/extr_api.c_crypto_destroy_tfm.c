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
struct crypto_tfm {int /*<<< orphan*/  exit; struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int /*<<< orphan*/  (* cra_exit ) (struct crypto_tfm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_exit_ops (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  kzfree (void*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_tfm*) ; 
 scalar_t__ unlikely (int) ; 

void crypto_destroy_tfm(void *mem, struct crypto_tfm *tfm)
{
	struct crypto_alg *alg;

	if (unlikely(!mem))
		return;

	alg = tfm->__crt_alg;

	if (!tfm->exit && alg->cra_exit)
		alg->cra_exit(tfm);
	crypto_exit_ops(tfm);
	crypto_mod_put(alg);
	kzfree(mem);
}