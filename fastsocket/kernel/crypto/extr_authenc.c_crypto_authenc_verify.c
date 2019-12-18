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
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  sg; int /*<<< orphan*/  complete; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/ * (* authenc_ahash_t ) (struct aead_request*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EBADMSG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 struct authenc_request_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  authenc_verify_ahash_done ; 
 int /*<<< orphan*/  authenc_verify_ahash_update_done ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_authenc_verify(struct aead_request *req,
				 authenc_ahash_t authenc_ahash_fn)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	u8 *ohash;
	u8 *ihash;
	unsigned int authsize;

	areq_ctx->complete = authenc_verify_ahash_done;
	areq_ctx->complete = authenc_verify_ahash_update_done;

	ohash = authenc_ahash_fn(req, CRYPTO_TFM_REQ_MAY_SLEEP);
	if (IS_ERR(ohash))
		return PTR_ERR(ohash);

	authsize = crypto_aead_authsize(authenc);
	ihash = ohash + authsize;
	scatterwalk_map_and_copy(ihash, areq_ctx->sg, areq_ctx->cryptlen,
				 authsize, 0);
	return memcmp(ihash, ohash, authsize) ? -EBADMSG: 0;
}