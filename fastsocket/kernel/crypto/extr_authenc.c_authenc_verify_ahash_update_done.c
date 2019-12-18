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
struct crypto_authenc_ctx {int /*<<< orphan*/  enc; scalar_t__ reqoff; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  sg; int /*<<< orphan*/  complete; scalar_t__ tail; } ;
struct ahash_request {int /*<<< orphan*/ * result; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; } ;
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EBADMSG ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 void* aead_request_ctx (struct aead_request*) ; 
 int aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authenc_request_complete (struct aead_request*,int) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_finup (struct ahash_request*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void authenc_verify_ahash_update_done(struct crypto_async_request *areq,
					     int err)
{
	u8 *ihash;
	unsigned int authsize;
	struct ablkcipher_request *abreq;
	struct aead_request *req = areq->data;
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ctx->reqoff);

	if (err)
		goto out;

	ahash_request_set_crypt(ahreq, areq_ctx->sg, ahreq->result,
				areq_ctx->cryptlen);
	ahash_request_set_callback(ahreq, aead_request_flags(req) &
					  CRYPTO_TFM_REQ_MAY_SLEEP,
				   areq_ctx->complete, req);

	err = crypto_ahash_finup(ahreq);
	if (err)
		goto out;

	authsize = crypto_aead_authsize(authenc);
	ihash = ahreq->result + authsize;
	scatterwalk_map_and_copy(ihash, areq_ctx->sg, areq_ctx->cryptlen,
				 authsize, 0);

	err = memcmp(ihash, ahreq->result, authsize) ? -EBADMSG: 0;
	if (err)
		goto out;

	abreq = aead_request_ctx(req);
	ablkcipher_request_set_tfm(abreq, ctx->enc);
	ablkcipher_request_set_callback(abreq, aead_request_flags(req),
					req->base.complete, req->base.data);
	ablkcipher_request_set_crypt(abreq, req->src, req->dst,
				     req->cryptlen, req->iv);

	err = crypto_ablkcipher_decrypt(abreq);

out:
	authenc_request_complete(req, err);
}