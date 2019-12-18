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
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_givcrypt_request {int dummy; } ;
struct crypto_authenc_ctx {int /*<<< orphan*/  enc; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct aead_givcrypt_request {int /*<<< orphan*/  seq; int /*<<< orphan*/ * giv; struct aead_request areq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 struct crypto_aead* aead_givcrypt_reqtfm (struct aead_givcrypt_request*) ; 
 struct skcipher_givcrypt_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_authenc_genicv (struct aead_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_authenc_givencrypt_done ; 
 int crypto_skcipher_givencrypt (struct skcipher_givcrypt_request*) ; 
 int /*<<< orphan*/  skcipher_givcrypt_set_callback (struct skcipher_givcrypt_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  skcipher_givcrypt_set_crypt (struct skcipher_givcrypt_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_givcrypt_set_giv (struct skcipher_givcrypt_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_givcrypt_set_tfm (struct skcipher_givcrypt_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_authenc_givencrypt(struct aead_givcrypt_request *req)
{
	struct crypto_aead *authenc = aead_givcrypt_reqtfm(req);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct aead_request *areq = &req->areq;
	struct skcipher_givcrypt_request *greq = aead_request_ctx(areq);
	u8 *iv = req->giv;
	int err;

	skcipher_givcrypt_set_tfm(greq, ctx->enc);
	skcipher_givcrypt_set_callback(greq, aead_request_flags(areq),
				       crypto_authenc_givencrypt_done, areq);
	skcipher_givcrypt_set_crypt(greq, areq->src, areq->dst, areq->cryptlen,
				    areq->iv);
	skcipher_givcrypt_set_giv(greq, iv, req->seq);

	err = crypto_skcipher_givencrypt(greq);
	if (err)
		return err;

	return crypto_authenc_genicv(areq, iv, CRYPTO_TFM_REQ_MAY_SLEEP);
}