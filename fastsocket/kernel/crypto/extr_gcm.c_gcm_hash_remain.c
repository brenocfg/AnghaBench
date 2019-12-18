#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ahash_request {int dummy; } ;
struct TYPE_2__ {struct ahash_request ahreq; } ;
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  src; TYPE_1__ u; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  gcm_zeroes ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int gcm_hash_remain(struct aead_request *req,
			   struct crypto_gcm_req_priv_ctx *pctx,
			   unsigned int remain,
			   crypto_completion_t complete)
{
	struct ahash_request *ahreq = &pctx->u.ahreq;

	ahash_request_set_callback(ahreq, aead_request_flags(req),
				   complete, req);
	sg_init_one(pctx->src, gcm_zeroes, remain);
	ahash_request_set_crypt(ahreq, pctx->src, NULL, remain);

	return crypto_ahash_update(ahreq);
}