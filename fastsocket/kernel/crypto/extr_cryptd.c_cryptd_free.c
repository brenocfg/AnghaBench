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
struct hashd_instance_ctx {int /*<<< orphan*/  spawn; } ;
struct TYPE_3__ {int cra_flags; } ;
struct crypto_instance {TYPE_1__ alg; } ;
struct cryptd_instance_ctx {int /*<<< orphan*/  spawn; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct aead_instance_ctx {TYPE_2__ aead_spawn; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 struct crypto_instance* ahash_instance (struct crypto_instance*) ; 
 int /*<<< orphan*/  crypto_drop_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_spawn (int /*<<< orphan*/ *) ; 
 void* crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

__attribute__((used)) static void cryptd_free(struct crypto_instance *inst)
{
	struct cryptd_instance_ctx *ctx = crypto_instance_ctx(inst);
	struct hashd_instance_ctx *hctx = crypto_instance_ctx(inst);
	struct aead_instance_ctx *aead_ctx = crypto_instance_ctx(inst);

	switch (inst->alg.cra_flags & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_AHASH:
		crypto_drop_shash(&hctx->spawn);
		kfree(ahash_instance(inst));
		return;
	case CRYPTO_ALG_TYPE_AEAD:
		crypto_drop_spawn(&aead_ctx->aead_spawn.base);
		kfree(inst);
		return;
	default:
		crypto_drop_spawn(&ctx->spawn);
		kfree(inst);
	}
}