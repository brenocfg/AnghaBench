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
struct eseqiv_ctx {int dummy; } ;
struct TYPE_3__ {scalar_t__ ivsize; int /*<<< orphan*/  givencrypt; } ;
struct TYPE_4__ {scalar_t__ cra_blocksize; int cra_ctxsize; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; } ;
struct crypto_instance {TYPE_2__ alg; } ;

/* Variables and functions */
 int EINVAL ; 
 struct crypto_instance* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 int crypto_get_default_rng () ; 
 int /*<<< orphan*/  crypto_put_default_rng () ; 
 int /*<<< orphan*/  eseqiv_givencrypt_first ; 
 int /*<<< orphan*/  eseqiv_init ; 
 int /*<<< orphan*/  eseqiv_tmpl ; 
 struct crypto_instance* skcipher_geniv_alloc (int /*<<< orphan*/ *,struct rtattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_geniv_exit ; 
 int /*<<< orphan*/  skcipher_geniv_free (struct crypto_instance*) ; 

__attribute__((used)) static struct crypto_instance *eseqiv_alloc(struct rtattr **tb)
{
	struct crypto_instance *inst;
	int err;

	err = crypto_get_default_rng();
	if (err)
		return ERR_PTR(err);

	inst = skcipher_geniv_alloc(&eseqiv_tmpl, tb, 0, 0);
	if (IS_ERR(inst))
		goto put_rng;

	err = -EINVAL;
	if (inst->alg.cra_ablkcipher.ivsize != inst->alg.cra_blocksize)
		goto free_inst;

	inst->alg.cra_ablkcipher.givencrypt = eseqiv_givencrypt_first;

	inst->alg.cra_init = eseqiv_init;
	inst->alg.cra_exit = skcipher_geniv_exit;

	inst->alg.cra_ctxsize = sizeof(struct eseqiv_ctx);
	inst->alg.cra_ctxsize += inst->alg.cra_ablkcipher.ivsize;

out:
	return inst;

free_inst:
	skcipher_geniv_free(inst);
	inst = ERR_PTR(err);
put_rng:
	crypto_put_default_rng();
	goto out;
}