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
struct crypto_rfc4543_req_ctx {int /*<<< orphan*/  auth_tag; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct aead_request* crypto_rfc4543_crypt (struct aead_request*,int) ; 
 struct crypto_rfc4543_req_ctx* crypto_rfc4543_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crypto_rfc4543_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4543_req_ctx *rctx = crypto_rfc4543_reqctx(req);
	struct aead_request *subreq;
	int err;

	subreq = crypto_rfc4543_crypt(req, 1);
	err = crypto_aead_encrypt(subreq);
	if (err)
		return err;

	scatterwalk_map_and_copy(rctx->auth_tag, req->dst, req->cryptlen,
				 crypto_aead_authsize(aead), 1);

	return 0;
}