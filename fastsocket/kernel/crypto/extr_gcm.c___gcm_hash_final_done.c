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
struct crypto_gcm_ghash_ctx {int /*<<< orphan*/  (* complete ) (struct aead_request*,int) ;} ;
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  iauth_tag; int /*<<< orphan*/  auth_tag; struct crypto_gcm_ghash_ctx ghash_ctx; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct aead_request*,int) ; 

__attribute__((used)) static void __gcm_hash_final_done(struct aead_request *req, int err)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	if (!err)
		crypto_xor(pctx->auth_tag, pctx->iauth_tag, 16);

	gctx->complete(req, err);
}