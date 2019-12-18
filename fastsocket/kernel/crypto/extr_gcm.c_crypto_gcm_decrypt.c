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
struct crypto_gcm_ghash_ctx {unsigned int cryptlen; int /*<<< orphan*/  complete; int /*<<< orphan*/  src; } ;
struct ablkcipher_request {int dummy; } ;
struct TYPE_2__ {struct ablkcipher_request abreq; } ;
struct crypto_gcm_req_priv_ctx {struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_gcm_init_crypt (struct ablkcipher_request*,struct aead_request*,unsigned int) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int crypto_gcm_verify (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 
 int /*<<< orphan*/  gcm_dec_hash_done ; 
 int /*<<< orphan*/  gcm_decrypt_done ; 
 int gcm_hash (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 

__attribute__((used)) static int crypto_gcm_decrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct ablkcipher_request *abreq = &pctx->u.abreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int cryptlen = req->cryptlen;
	int err;

	if (cryptlen < authsize)
		return -EINVAL;
	cryptlen -= authsize;

	gctx->src = req->src;
	gctx->cryptlen = cryptlen;
	gctx->complete = gcm_dec_hash_done;

	err = gcm_hash(req, pctx);
	if (err)
		return err;

	ablkcipher_request_set_callback(abreq, aead_request_flags(req),
					gcm_decrypt_done, req);
	crypto_gcm_init_crypt(abreq, req, cryptlen);
	err = crypto_ablkcipher_decrypt(abreq);
	if (err)
		return err;

	return crypto_gcm_verify(req, pctx);
}