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
struct lzo_ctx {int /*<<< orphan*/  lzo_comp_mem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct lzo_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lzo_exit(struct crypto_tfm *tfm)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	vfree(ctx->lzo_comp_mem);
}