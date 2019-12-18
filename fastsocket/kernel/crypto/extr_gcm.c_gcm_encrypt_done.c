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
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  iauth_tag; int /*<<< orphan*/  auth_tag; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcm_enc_copy_hash (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 
 int gcm_hash (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 

__attribute__((used)) static void gcm_encrypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);

	if (!err) {
		err = gcm_hash(req, pctx);
		if (err == -EINPROGRESS || err == -EBUSY)
			return;
		else if (!err) {
			crypto_xor(pctx->auth_tag, pctx->iauth_tag, 16);
			gcm_enc_copy_hash(req, pctx);
		}
	}

	aead_request_complete(req, err);
}