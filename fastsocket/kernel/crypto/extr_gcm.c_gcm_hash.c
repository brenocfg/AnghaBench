#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_gcm_ghash_ctx {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  src; } ;
struct ahash_request {int dummy; } ;
struct TYPE_3__ {struct ahash_request ahreq; } ;
struct crypto_gcm_req_priv_ctx {struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct crypto_gcm_ctx {int /*<<< orphan*/  ghash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  assoc; TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,int /*<<< orphan*/ ) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 struct crypto_gcm_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcm_hash_assoc_done ; 
 int /*<<< orphan*/  gcm_hash_assoc_remain_done ; 
 int /*<<< orphan*/  gcm_hash_crypt_done ; 
 int /*<<< orphan*/  gcm_hash_crypt_remain_done ; 
 int gcm_hash_final (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 
 int /*<<< orphan*/  gcm_hash_init_done ; 
 int gcm_hash_len (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 
 int gcm_hash_remain (struct aead_request*,struct crypto_gcm_req_priv_ctx*,unsigned int,int /*<<< orphan*/ ) ; 
 int gcm_hash_update (struct aead_request*,struct crypto_gcm_req_priv_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int gcm_remain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_hash(struct aead_request *req,
		    struct crypto_gcm_req_priv_ctx *pctx)
{
	struct ahash_request *ahreq = &pctx->u.ahreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	struct crypto_gcm_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	unsigned int remain;
	crypto_completion_t complete;
	int err;

	ahash_request_set_tfm(ahreq, ctx->ghash);

	ahash_request_set_callback(ahreq, aead_request_flags(req),
				   gcm_hash_init_done, req);
	err = crypto_ahash_init(ahreq);
	if (err)
		return err;
	remain = gcm_remain(req->assoclen);
	complete = remain ? gcm_hash_assoc_done : gcm_hash_assoc_remain_done;
	err = gcm_hash_update(req, pctx, complete, req->assoc, req->assoclen);
	if (err)
		return err;
	if (remain) {
		err = gcm_hash_remain(req, pctx, remain,
				      gcm_hash_assoc_remain_done);
		if (err)
			return err;
	}
	remain = gcm_remain(gctx->cryptlen);
	complete = remain ? gcm_hash_crypt_done : gcm_hash_crypt_remain_done;
	err = gcm_hash_update(req, pctx, complete, gctx->src, gctx->cryptlen);
	if (err)
		return err;
	if (remain) {
		err = gcm_hash_remain(req, pctx, remain,
				      gcm_hash_crypt_remain_done);
		if (err)
			return err;
	}
	err = gcm_hash_len(req, pctx);
	if (err)
		return err;
	err = gcm_hash_final(req, pctx);
	if (err)
		return err;

	return 0;
}