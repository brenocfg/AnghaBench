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
struct crypto_gcm_req_priv_ctx {int dummy; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int crypto_gcm_verify (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 

__attribute__((used)) static void gcm_decrypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);

	if (!err)
		err = crypto_gcm_verify(req, pctx);

	aead_request_complete(req, err);
}