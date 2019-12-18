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
struct crypto_tfm {TYPE_1__ crt_ablkcipher; scalar_t__ __crt_alg; } ;
struct crypto_skcipher_spawn {int dummy; } ;
struct crypto_rfc3686_req_ctx {int dummy; } ;
struct crypto_rfc3686_ctx {struct crypto_ablkcipher* child; } ;
struct crypto_instance {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_ablkcipher*) ; 
 int PTR_ERR (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_reqsize (struct crypto_ablkcipher*) ; 
 struct crypto_skcipher_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_ablkcipher* crypto_spawn_skcipher (struct crypto_skcipher_spawn*) ; 
 unsigned long crypto_tfm_alg_alignmask (struct crypto_tfm*) ; 
 struct crypto_rfc3686_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static int crypto_rfc3686_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct crypto_skcipher_spawn *spawn = crypto_instance_ctx(inst);
	struct crypto_rfc3686_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_ablkcipher *cipher;
	unsigned long align;

	cipher = crypto_spawn_skcipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;

	align = crypto_tfm_alg_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	tfm->crt_ablkcipher.reqsize = align +
		sizeof(struct crypto_rfc3686_req_ctx) +
		crypto_ablkcipher_reqsize(cipher);

	return 0;
}