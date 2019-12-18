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
struct aesni_lrw_ctx {int /*<<< orphan*/  lrw_table; } ;

/* Variables and functions */
 struct aesni_lrw_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  lrw_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lrw_aesni_exit_tfm(struct crypto_tfm *tfm)
{
	struct aesni_lrw_ctx *ctx = crypto_tfm_ctx(tfm);

	lrw_free_table(&ctx->lrw_table);
}