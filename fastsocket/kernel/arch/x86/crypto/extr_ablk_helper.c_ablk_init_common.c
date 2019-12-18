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
struct TYPE_2__ {scalar_t__ reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct cryptd_ablkcipher {int /*<<< orphan*/  base; } ;
struct async_helper_ctx {struct cryptd_ablkcipher* cryptd_tfm; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct cryptd_ablkcipher*) ; 
 int PTR_ERR (struct cryptd_ablkcipher*) ; 
 struct cryptd_ablkcipher* cryptd_alloc_ablkcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_reqsize (int /*<<< orphan*/ *) ; 
 struct async_helper_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

int ablk_init_common(struct crypto_tfm *tfm, const char *drv_name)
{
	struct async_helper_ctx *ctx = crypto_tfm_ctx(tfm);
	struct cryptd_ablkcipher *cryptd_tfm;

	cryptd_tfm = cryptd_alloc_ablkcipher(drv_name, 0, 0);
	if (IS_ERR(cryptd_tfm))
		return PTR_ERR(cryptd_tfm);

	ctx->cryptd_tfm = cryptd_tfm;
	tfm->crt_ablkcipher.reqsize = sizeof(struct ablkcipher_request) +
		crypto_ablkcipher_reqsize(&cryptd_tfm->base);

	return 0;
}