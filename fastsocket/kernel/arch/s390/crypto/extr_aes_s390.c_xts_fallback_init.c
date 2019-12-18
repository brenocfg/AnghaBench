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
struct s390_xts_ctx {int /*<<< orphan*/  fallback; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_2__ {char* cra_name; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_blkcipher (char const*,int /*<<< orphan*/ ,int) ; 
 struct s390_xts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int xts_fallback_init(struct crypto_tfm *tfm)
{
	const char *name = tfm->__crt_alg->cra_name;
	struct s390_xts_ctx *xts_ctx = crypto_tfm_ctx(tfm);

	xts_ctx->fallback = crypto_alloc_blkcipher(name, 0,
			CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK);

	if (IS_ERR(xts_ctx->fallback)) {
		pr_err("Allocating XTS fallback algorithm %s failed\n",
		       name);
		return PTR_ERR(xts_ctx->fallback);
	}
	return 0;
}