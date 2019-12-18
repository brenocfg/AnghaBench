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
struct crypto_gcm_ghash_ctx {scalar_t__ cryptlen; int /*<<< orphan*/  src; } ;
struct crypto_gcm_req_priv_ctx {struct crypto_gcm_ghash_ctx ghash_ctx; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  __gcm_hash_crypt_done (struct aead_request*,int) ; 
 int /*<<< orphan*/  __gcm_hash_crypt_remain_done (struct aead_request*,int) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  gcm_hash_crypt_done ; 
 int /*<<< orphan*/  gcm_hash_crypt_remain_done ; 
 int gcm_hash_update (struct aead_request*,struct crypto_gcm_req_priv_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int gcm_remain (scalar_t__) ; 

__attribute__((used)) static void __gcm_hash_assoc_remain_done(struct aead_request *req, int err)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	crypto_completion_t complete;
	unsigned int remain = 0;

	if (!err && gctx->cryptlen) {
		remain = gcm_remain(gctx->cryptlen);
		complete = remain ? gcm_hash_crypt_done :
			gcm_hash_crypt_remain_done;
		err = gcm_hash_update(req, pctx, complete,
				      gctx->src, gctx->cryptlen);
		if (err == -EINPROGRESS || err == -EBUSY)
			return;
	}

	if (remain)
		__gcm_hash_crypt_done(req, err);
	else
		__gcm_hash_crypt_remain_done(req, err);
}