#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct crypto_tfm {int dummy; } ;
struct async_helper_ctx {int /*<<< orphan*/  cryptd_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cryptd_free_ablkcipher (int /*<<< orphan*/ ) ; 
 struct async_helper_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

void ablk_exit(struct crypto_tfm *tfm)
{
	struct async_helper_ctx *ctx = crypto_tfm_ctx(tfm);

	cryptd_free_ablkcipher(ctx->cryptd_tfm);
}