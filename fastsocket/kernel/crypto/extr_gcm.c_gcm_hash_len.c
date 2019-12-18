#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* b; void* a; } ;
typedef  TYPE_2__ u128 ;
struct crypto_gcm_ghash_ctx {int cryptlen; } ;
struct ahash_request {int dummy; } ;
struct TYPE_4__ {struct ahash_request ahreq; } ;
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  src; int /*<<< orphan*/  iauth_tag; struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct aead_request {int assoclen; } ;
typedef  int /*<<< orphan*/  lengths ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* cpu_to_be64 (int) ; 
 int crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  gcm_hash_len_done ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gcm_hash_len(struct aead_request *req,
			struct crypto_gcm_req_priv_ctx *pctx)
{
	struct ahash_request *ahreq = &pctx->u.ahreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	u128 lengths;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64(gctx->cryptlen * 8);
	memcpy(pctx->iauth_tag, &lengths, 16);
	sg_init_one(pctx->src, pctx->iauth_tag, 16);
	ahash_request_set_callback(ahreq, aead_request_flags(req),
				   gcm_hash_len_done, req);
	ahash_request_set_crypt(ahreq, pctx->src,
				NULL, sizeof(lengths));

	return crypto_ahash_update(ahreq);
}