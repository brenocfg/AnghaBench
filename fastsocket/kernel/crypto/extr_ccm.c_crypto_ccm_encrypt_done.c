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
struct crypto_ccm_req_priv_ctx {int /*<<< orphan*/ * odata; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void crypto_ccm_encrypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	u8 *odata = pctx->odata;

	if (!err)
		scatterwalk_map_and_copy(odata, req->dst, req->cryptlen,
					 crypto_aead_authsize(aead), 1);
	aead_request_complete(req, err);
}