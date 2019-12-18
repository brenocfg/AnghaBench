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
struct async_helper_ctx {TYPE_1__* cryptd_tfm; } ;
struct ablkcipher_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int __ablk_encrypt (struct ablkcipher_request*) ; 
 struct ablkcipher_request* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ *) ; 
 struct async_helper_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  irq_fpu_usable () ; 
 int /*<<< orphan*/  memcpy (struct ablkcipher_request*,struct ablkcipher_request*,int) ; 

int ablk_encrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct async_helper_ctx *ctx = crypto_ablkcipher_ctx(tfm);

	if (!irq_fpu_usable()) {
		struct ablkcipher_request *cryptd_req =
			ablkcipher_request_ctx(req);

		memcpy(cryptd_req, req, sizeof(*req));
		ablkcipher_request_set_tfm(cryptd_req, &ctx->cryptd_tfm->base);

		return crypto_ablkcipher_encrypt(cryptd_req);
	} else {
		return __ablk_encrypt(req);
	}
}