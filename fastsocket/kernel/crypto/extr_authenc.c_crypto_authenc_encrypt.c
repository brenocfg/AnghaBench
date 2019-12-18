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
struct scatterlist {int dummy; } ;
struct crypto_authenc_ctx {struct crypto_ablkcipher* enc; } ;
struct crypto_aead {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct aead_request {unsigned int cryptlen; int /*<<< orphan*/  iv; int /*<<< orphan*/  src; struct scatterlist* dst; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,struct crypto_ablkcipher*) ; 
 struct ablkcipher_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 int crypto_ablkcipher_reqsize (struct crypto_ablkcipher*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_authenc_encrypt_done ; 
 int crypto_authenc_genicv (struct aead_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_authenc_encrypt(struct aead_request *req)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct ablkcipher_request *abreq = aead_request_ctx(req);
	struct crypto_ablkcipher *enc = ctx->enc;
	struct scatterlist *dst = req->dst;
	unsigned int cryptlen = req->cryptlen;
	u8 *iv = (u8 *)(abreq + 1) + crypto_ablkcipher_reqsize(enc);
	int err;

	ablkcipher_request_set_tfm(abreq, enc);
	ablkcipher_request_set_callback(abreq, aead_request_flags(req),
					crypto_authenc_encrypt_done, req);
	ablkcipher_request_set_crypt(abreq, req->src, dst, cryptlen, req->iv);

	memcpy(iv, req->iv, crypto_aead_ivsize(authenc));

	err = crypto_ablkcipher_encrypt(abreq);
	if (err)
		return err;

	return crypto_authenc_genicv(req, iv, CRYPTO_TFM_REQ_MAY_SLEEP);
}