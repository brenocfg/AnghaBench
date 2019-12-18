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
struct crypto_gcm_ghash_ctx {int /*<<< orphan*/  cryptlen; } ;
struct ablkcipher_request {int dummy; } ;
struct TYPE_2__ {struct ablkcipher_request abreq; } ;
struct crypto_gcm_req_priv_ctx {struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_gcm_init_crypt (struct ablkcipher_request*,struct aead_request*,int /*<<< orphan*/ ) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int crypto_gcm_verify (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 
 int /*<<< orphan*/  gcm_decrypt_done ; 

__attribute__((used)) static void gcm_dec_hash_done(struct aead_request *req, int err)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct ablkcipher_request *abreq = &pctx->u.abreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	if (!err) {
		ablkcipher_request_set_callback(abreq, aead_request_flags(req),
						gcm_decrypt_done, req);
		crypto_gcm_init_crypt(abreq, req, gctx->cryptlen);
		err = crypto_ablkcipher_decrypt(abreq);
		if (err == -EINPROGRESS || err == -EBUSY)
			return;
		else if (!err)
			err = crypto_gcm_verify(req, pctx);
	}

	aead_request_complete(req, err);
}