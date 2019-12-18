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
struct TYPE_4__ {int /*<<< orphan*/  blk; int /*<<< orphan*/  cip; } ;
struct s390_aes_ctx {TYPE_2__ fallback; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_3__ {char* cra_name; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_cipher (char const*,int /*<<< orphan*/ ,int) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int fallback_init_cip(struct crypto_tfm *tfm)
{
	const char *name = tfm->__crt_alg->cra_name;
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	sctx->fallback.cip = crypto_alloc_cipher(name, 0,
			CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK);

	if (IS_ERR(sctx->fallback.cip)) {
		pr_err("Allocating AES fallback algorithm %s failed\n",
		       name);
		return PTR_ERR(sctx->fallback.blk);
	}

	return 0;
}