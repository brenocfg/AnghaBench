#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtattr {int dummy; } ;
struct TYPE_3__ {scalar_t__ ivsize; int /*<<< orphan*/  givencrypt; } ;
struct TYPE_4__ {int cra_ctxsize; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_flags; } ;
struct crypto_instance {TYPE_2__ alg; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct crypto_attr_type {TYPE_2__ alg; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct chainiv_ctx {int dummy; } ;
struct async_chainiv_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 int PTR_ERR (struct crypto_instance*) ; 
 int /*<<< orphan*/  async_chainiv_exit ; 
 int /*<<< orphan*/  async_chainiv_givencrypt_first ; 
 int /*<<< orphan*/  async_chainiv_init ; 
 int /*<<< orphan*/  chainiv_givencrypt_first ; 
 int /*<<< orphan*/  chainiv_init ; 
 int /*<<< orphan*/  chainiv_tmpl ; 
 struct crypto_instance* crypto_get_attr_type (struct rtattr**) ; 
 int crypto_get_default_rng () ; 
 int /*<<< orphan*/  crypto_put_default_rng () ; 
 int /*<<< orphan*/  crypto_requires_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_instance* skcipher_geniv_alloc (int /*<<< orphan*/ *,struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_geniv_exit ; 

__attribute__((used)) static struct crypto_instance *chainiv_alloc(struct rtattr **tb)
{
	struct crypto_attr_type *algt;
	struct crypto_instance *inst;
	int err;

	algt = crypto_get_attr_type(tb);
	err = PTR_ERR(algt);
	if (IS_ERR(algt))
		return ERR_PTR(err);

	err = crypto_get_default_rng();
	if (err)
		return ERR_PTR(err);

	inst = skcipher_geniv_alloc(&chainiv_tmpl, tb, 0, 0);
	if (IS_ERR(inst))
		goto put_rng;

	inst->alg.cra_ablkcipher.givencrypt = chainiv_givencrypt_first;

	inst->alg.cra_init = chainiv_init;
	inst->alg.cra_exit = skcipher_geniv_exit;

	inst->alg.cra_ctxsize = sizeof(struct chainiv_ctx);

	if (!crypto_requires_sync(algt->type, algt->mask)) {
		inst->alg.cra_flags |= CRYPTO_ALG_ASYNC;

		inst->alg.cra_ablkcipher.givencrypt =
			async_chainiv_givencrypt_first;

		inst->alg.cra_init = async_chainiv_init;
		inst->alg.cra_exit = async_chainiv_exit;

		inst->alg.cra_ctxsize = sizeof(struct async_chainiv_ctx);
	}

	inst->alg.cra_ctxsize += inst->alg.cra_ablkcipher.ivsize;

out:
	return inst;

put_rng:
	crypto_put_default_rng();
	goto out;
}