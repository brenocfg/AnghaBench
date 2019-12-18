#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; int /*<<< orphan*/  geniv; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; int /*<<< orphan*/  ivsize; } ;
struct TYPE_6__ {int cra_flags; int cra_ctxsize; TYPE_2__ cra_ablkcipher; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/ * cra_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  geniv; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; int /*<<< orphan*/  ivsize; } ;
struct crypto_instance {TYPE_3__ alg; TYPE_1__ cra_blkcipher; } ;
struct crypto_alg {TYPE_3__ alg; TYPE_1__ cra_blkcipher; } ;
struct cryptd_queue {int dummy; } ;
struct cryptd_instance_ctx {int /*<<< orphan*/  spawn; struct cryptd_queue* queue; } ;
struct cryptd_blkcipher_ctx {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_TYPE_ABLKCIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 scalar_t__ IS_ERR (struct crypto_instance*) ; 
 int PTR_ERR (struct crypto_instance*) ; 
 struct crypto_instance* cryptd_alloc_instance (struct crypto_instance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cryptd_blkcipher_decrypt_enqueue ; 
 int /*<<< orphan*/  cryptd_blkcipher_encrypt_enqueue ; 
 int /*<<< orphan*/  cryptd_blkcipher_exit_tfm ; 
 int /*<<< orphan*/  cryptd_blkcipher_init_tfm ; 
 int /*<<< orphan*/  cryptd_blkcipher_setkey ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int /*<<< orphan*/  crypto_drop_spawn (int /*<<< orphan*/ *) ; 
 struct crypto_instance* crypto_get_attr_alg (struct rtattr**,int /*<<< orphan*/ ,int) ; 
 int crypto_init_spawn (int /*<<< orphan*/ *,struct crypto_instance*,struct crypto_instance*,int) ; 
 struct cryptd_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_instance*) ; 
 int crypto_register_instance (struct crypto_template*,struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

__attribute__((used)) static int cryptd_create_blkcipher(struct crypto_template *tmpl,
				   struct rtattr **tb,
				   struct cryptd_queue *queue)
{
	struct cryptd_instance_ctx *ctx;
	struct crypto_instance *inst;
	struct crypto_alg *alg;
	int err;

	alg = crypto_get_attr_alg(tb, CRYPTO_ALG_TYPE_BLKCIPHER,
				  CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	inst = cryptd_alloc_instance(alg, 0, sizeof(*ctx));
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	ctx = crypto_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_init_spawn(&ctx->spawn, alg, inst,
				CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_ASYNC);
	if (err)
		goto out_free_inst;

	inst->alg.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER | CRYPTO_ALG_ASYNC;
	inst->alg.cra_type = &crypto_ablkcipher_type;

	inst->alg.cra_ablkcipher.ivsize = alg->cra_blkcipher.ivsize;
	inst->alg.cra_ablkcipher.min_keysize = alg->cra_blkcipher.min_keysize;
	inst->alg.cra_ablkcipher.max_keysize = alg->cra_blkcipher.max_keysize;

	inst->alg.cra_ablkcipher.geniv = alg->cra_blkcipher.geniv;

	inst->alg.cra_ctxsize = sizeof(struct cryptd_blkcipher_ctx);

	inst->alg.cra_init = cryptd_blkcipher_init_tfm;
	inst->alg.cra_exit = cryptd_blkcipher_exit_tfm;

	inst->alg.cra_ablkcipher.setkey = cryptd_blkcipher_setkey;
	inst->alg.cra_ablkcipher.encrypt = cryptd_blkcipher_encrypt_enqueue;
	inst->alg.cra_ablkcipher.decrypt = cryptd_blkcipher_decrypt_enqueue;

	err = crypto_register_instance(tmpl, inst);
	if (err) {
		crypto_drop_spawn(&ctx->spawn);
out_free_inst:
		kfree(inst);
	}

out_put_alg:
	crypto_mod_put(alg);
	return err;
}