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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  info; } ;
struct crypto_rfc3686_req_ctx {int /*<<< orphan*/ * iv; struct ablkcipher_request subreq; } ;
struct crypto_rfc3686_ctx {int /*<<< orphan*/  nonce; struct crypto_ablkcipher* child; } ;
struct crypto_ablkcipher {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 scalar_t__ PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 unsigned long crypto_ablkcipher_alignmask (struct crypto_ablkcipher*) ; 
 struct crypto_rfc3686_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crypto_rfc3686_crypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct crypto_rfc3686_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	struct crypto_ablkcipher *child = ctx->child;
	unsigned long align = crypto_ablkcipher_alignmask(tfm);
	struct crypto_rfc3686_req_ctx *rctx =
		(void *)PTR_ALIGN((u8 *)ablkcipher_request_ctx(req), align + 1);
	struct ablkcipher_request *subreq = &rctx->subreq;
	u8 *iv = rctx->iv;

	/* set up counter block */
	memcpy(iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE);
	memcpy(iv + CTR_RFC3686_NONCE_SIZE, req->info, CTR_RFC3686_IV_SIZE);

	/* initialize counter portion of counter block */
	*(__be32 *)(iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
		cpu_to_be32(1);

	ablkcipher_request_set_tfm(subreq, child);
	ablkcipher_request_set_callback(subreq, req->base.flags,
					req->base.complete, req->base.data);
	ablkcipher_request_set_crypt(subreq, req->src, req->dst, req->nbytes,
				     iv);

	return crypto_ablkcipher_encrypt(subreq);
}