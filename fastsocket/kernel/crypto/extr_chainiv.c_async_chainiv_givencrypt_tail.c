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
struct skcipher_givcrypt_request {int /*<<< orphan*/  giv; } ;
struct crypto_ablkcipher {int dummy; } ;
struct async_chainiv_ctx {int /*<<< orphan*/  iv; scalar_t__ err; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int async_chainiv_schedule_work (struct async_chainiv_ctx*) ; 
 struct async_chainiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct ablkcipher_request* skcipher_givcrypt_reqctx (struct skcipher_givcrypt_request*) ; 
 struct crypto_ablkcipher* skcipher_givcrypt_reqtfm (struct skcipher_givcrypt_request*) ; 

__attribute__((used)) static int async_chainiv_givencrypt_tail(struct skcipher_givcrypt_request *req)
{
	struct crypto_ablkcipher *geniv = skcipher_givcrypt_reqtfm(req);
	struct async_chainiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);
	struct ablkcipher_request *subreq = skcipher_givcrypt_reqctx(req);
	unsigned int ivsize = crypto_ablkcipher_ivsize(geniv);

	memcpy(req->giv, ctx->iv, ivsize);
	memcpy(subreq->info, ctx->iv, ivsize);

	ctx->err = crypto_ablkcipher_encrypt(subreq);
	if (ctx->err)
		goto out;

	memcpy(ctx->iv, subreq->info, ivsize);

out:
	return async_chainiv_schedule_work(ctx);
}