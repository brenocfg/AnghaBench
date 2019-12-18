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
struct crypto_ablkcipher {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; scalar_t__ flags; int /*<<< orphan*/  info; } ;
struct async_helper_ctx {int /*<<< orphan*/  cryptd_tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  info; } ;
struct TYPE_2__ {int (* encrypt ) (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cryptd_ablkcipher_child (int /*<<< orphan*/ ) ; 
 struct async_helper_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 TYPE_1__* crypto_blkcipher_crt (int /*<<< orphan*/ ) ; 
 int stub1 (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __ablk_encrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct async_helper_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	struct blkcipher_desc desc;

	desc.tfm = cryptd_ablkcipher_child(ctx->cryptd_tfm);
	desc.info = req->info;
	desc.flags = 0;

	return crypto_blkcipher_crt(desc.tfm)->encrypt(
		&desc, req->dst, req->src, req->nbytes);
}