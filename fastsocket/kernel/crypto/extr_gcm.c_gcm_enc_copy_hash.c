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
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/ * auth_tag; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gcm_enc_copy_hash(struct aead_request *req,
			      struct crypto_gcm_req_priv_ctx *pctx)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	u8 *auth_tag = pctx->auth_tag;

	scatterwalk_map_and_copy(auth_tag, req->dst, req->cryptlen,
				 crypto_aead_authsize(aead), 1);
}