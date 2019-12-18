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
struct crypto_authenc_ctx {scalar_t__ reqoff; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  sg; int /*<<< orphan*/  complete; scalar_t__ tail; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 struct authenc_request_ctx* aead_request_ctx (struct aead_request*) ; 
 int aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authenc_request_complete (struct aead_request*,int) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_finup (struct ahash_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void authenc_geniv_ahash_update_done(struct crypto_async_request *areq,
					    int err)
{
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

	scatterwalk_map_and_copy(ahreq->result, areq_ctx->sg,
				 areq_ctx->cryptlen,
				 crypto_aead_authsize(authenc), 1);

out:
	authenc_request_complete(req, err);
}