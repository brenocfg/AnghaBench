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
struct crypto_authenc_ctx {int reqoff; struct crypto_ahash* auth; } ;
struct crypto_ahash {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {int /*<<< orphan*/  complete; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  sg; int /*<<< orphan*/ * tail; } ;
struct ahash_request {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 struct authenc_request_ctx* aead_request_ctx (struct aead_request*) ; 
 unsigned int aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,unsigned int,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,struct crypto_ahash*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_ahash_alignmask (struct crypto_ahash*) ; 
 int crypto_ahash_digest (struct ahash_request*) ; 

__attribute__((used)) static u8 *crypto_authenc_ahash(struct aead_request *req, unsigned int flags)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct crypto_ahash *auth = ctx->auth;
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ctx->reqoff);
	u8 *hash = areq_ctx->tail;
	int err;

	hash = (u8 *)ALIGN((unsigned long)hash + crypto_ahash_alignmask(auth),
			   crypto_ahash_alignmask(auth) + 1);

	ahash_request_set_tfm(ahreq, auth);
	ahash_request_set_crypt(ahreq, areq_ctx->sg, hash,
				areq_ctx->cryptlen);
	ahash_request_set_callback(ahreq, aead_request_flags(req) & flags,
				   areq_ctx->complete, req);

	err = crypto_ahash_digest(ahreq);
	if (err)
		return ERR_PTR(err);

	return hash;
}