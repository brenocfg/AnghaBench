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
 int ENOMEM ; 
 int /*<<< orphan*/  LZO1X_MEM_COMPRESS ; 
 struct lzo_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lzo_init(struct crypto_tfm *tfm)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->lzo_comp_mem = vmalloc(LZO1X_MEM_COMPRESS);
	if (!ctx->lzo_comp_mem)
		return -ENOMEM;

	return 0;
}