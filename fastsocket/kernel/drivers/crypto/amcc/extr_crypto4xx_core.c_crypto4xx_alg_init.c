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
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int cra_flags; } ;
struct crypto4xx_ctx {scalar_t__ sa_len; scalar_t__ sa_out_dma_addr; scalar_t__ sa_in_dma_addr; int /*<<< orphan*/ * sa_out; int /*<<< orphan*/ * sa_in; int /*<<< orphan*/  dev; } ;
struct crypto4xx_alg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct crypto4xx_alg* crypto_alg_to_crypto4xx_alg (struct crypto_alg*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int crypto4xx_alg_init(struct crypto_tfm *tfm)
{
	struct crypto_alg *alg = tfm->__crt_alg;
	struct crypto4xx_alg *amcc_alg = crypto_alg_to_crypto4xx_alg(alg);
	struct crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->dev = amcc_alg->dev;
	ctx->sa_in = NULL;
	ctx->sa_out = NULL;
	ctx->sa_in_dma_addr = 0;
	ctx->sa_out_dma_addr = 0;
	ctx->sa_len = 0;

	switch (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) {
	default:
		tfm->crt_ablkcipher.reqsize = sizeof(struct crypto4xx_ctx);
		break;
	case CRYPTO_ALG_TYPE_AHASH:
		crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
					 sizeof(struct crypto4xx_ctx));
		break;
	}

	return 0;
}