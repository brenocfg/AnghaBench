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
struct shash_desc {int /*<<< orphan*/  flags; struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct cryptd_hash_request_ctx {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;struct shash_desc desc; } ;
struct cryptd_hash_ctx {struct crypto_shash* child; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct cryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int crypto_shash_init (struct shash_desc*) ; 
 struct cryptd_hash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cryptd_hash_init(struct crypto_async_request *req_async, int err)
{
	struct cryptd_hash_ctx *ctx = crypto_tfm_ctx(req_async->tfm);
	struct crypto_shash *child = ctx->child;
	struct ahash_request *req = ahash_request_cast(req_async);
	struct cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct shash_desc *desc = &rctx->desc;

	if (unlikely(err == -EINPROGRESS))
		goto out;

	desc->tfm = child;
	desc->flags = CRYPTO_TFM_REQ_MAY_SLEEP;

	err = crypto_shash_init(desc);

	req->base.complete = rctx->complete;

out:
	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();
}