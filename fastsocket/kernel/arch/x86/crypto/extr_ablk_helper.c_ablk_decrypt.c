#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_ablkcipher {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; scalar_t__ flags; int /*<<< orphan*/  info; } ;
struct async_helper_ctx {TYPE_2__* cryptd_tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  info; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int (* decrypt ) (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ablkcipher_request* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cryptd_ablkcipher_child (TYPE_2__*) ; 
 struct async_helper_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 TYPE_1__* crypto_blkcipher_crt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_fpu_usable () ; 
 int /*<<< orphan*/  memcpy (struct ablkcipher_request*,struct ablkcipher_request*,int) ; 
 int stub1 (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ablk_decrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct async_helper_ctx *ctx = crypto_ablkcipher_ctx(tfm);

	if (!irq_fpu_usable()) {
		struct ablkcipher_request *cryptd_req =
			ablkcipher_request_ctx(req);

		memcpy(cryptd_req, req, sizeof(*req));
		ablkcipher_request_set_tfm(cryptd_req, &ctx->cryptd_tfm->base);

		return crypto_ablkcipher_decrypt(cryptd_req);
	} else {
		struct blkcipher_desc desc;

		desc.tfm = cryptd_ablkcipher_child(ctx->cryptd_tfm);
		desc.info = req->info;
		desc.flags = 0;

		return crypto_blkcipher_crt(desc.tfm)->decrypt(
			&desc, req->dst, req->src, req->nbytes);
	}
}