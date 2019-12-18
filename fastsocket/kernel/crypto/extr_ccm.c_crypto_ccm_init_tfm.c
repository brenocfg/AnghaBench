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
struct TYPE_2__ {scalar_t__ reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_aead; scalar_t__ __crt_alg; } ;
struct crypto_instance {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_ccm_req_priv_ctx {int dummy; } ;
struct crypto_ccm_ctx {struct crypto_cipher* ctr; struct crypto_cipher* cipher; } ;
typedef  struct crypto_cipher crypto_ablkcipher ;
struct ccm_instance_ctx {int /*<<< orphan*/  ctr; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 scalar_t__ crypto_ablkcipher_reqsize (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 
 struct ccm_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_cipher* crypto_spawn_cipher (int /*<<< orphan*/ *) ; 
 struct crypto_cipher* crypto_spawn_skcipher (int /*<<< orphan*/ *) ; 
 unsigned long crypto_tfm_alg_alignmask (struct crypto_tfm*) ; 
 struct crypto_ccm_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static int crypto_ccm_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct ccm_instance_ctx *ictx = crypto_instance_ctx(inst);
	struct crypto_ccm_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_cipher *cipher;
	struct crypto_ablkcipher *ctr;
	unsigned long align;
	int err;

	cipher = crypto_spawn_cipher(&ictx->cipher);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctr = crypto_spawn_skcipher(&ictx->ctr);
	err = PTR_ERR(ctr);
	if (IS_ERR(ctr))
		goto err_free_cipher;

	ctx->cipher = cipher;
	ctx->ctr = ctr;

	align = crypto_tfm_alg_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	tfm->crt_aead.reqsize = align +
				sizeof(struct crypto_ccm_req_priv_ctx) +
				crypto_ablkcipher_reqsize(ctr);

	return 0;

err_free_cipher:
	crypto_free_cipher(cipher);
	return err;
}