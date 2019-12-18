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
struct crypto_ccm_req_priv_ctx {int /*<<< orphan*/  odata; int /*<<< orphan*/  auth_tag; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ccm_auth (struct aead_request*,int /*<<< orphan*/ ,unsigned int) ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_ccm_decrypt_done(struct crypto_async_request *areq,
				   int err)
{
	struct aead_request *req = areq->data;
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int cryptlen = req->cryptlen - authsize;

	if (!err) {
		err = crypto_ccm_auth(req, req->dst, cryptlen);
		if (!err && memcmp(pctx->auth_tag, pctx->odata, authsize))
			err = -EBADMSG;
	}
	aead_request_complete(req, err);
}