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
struct crypto_blkcipher {int dummy; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct cryptd_blkcipher_ctx {struct crypto_blkcipher* child; } ;
struct TYPE_2__ {int /*<<< orphan*/  encrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ablkcipher_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  cryptd_blkcipher_crypt (int /*<<< orphan*/ ,struct crypto_blkcipher*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* crypto_blkcipher_crt (struct crypto_blkcipher*) ; 
 struct cryptd_blkcipher_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cryptd_blkcipher_encrypt(struct crypto_async_request *req, int err)
{
	struct cryptd_blkcipher_ctx *ctx = crypto_tfm_ctx(req->tfm);
	struct crypto_blkcipher *child = ctx->child;

	cryptd_blkcipher_crypt(ablkcipher_request_cast(req), child, err,
			       crypto_blkcipher_crt(child)->encrypt);
}