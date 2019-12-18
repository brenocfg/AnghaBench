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
struct crypto_instance {int dummy; } ;
struct authenc_instance_ctx {int /*<<< orphan*/  auth; int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 struct authenc_instance_ctx* crypto_instance_ctx (struct crypto_instance*) ; 
 int /*<<< orphan*/  kfree (struct crypto_instance*) ; 

__attribute__((used)) static void crypto_authenc_free(struct crypto_instance *inst)
{
	struct authenc_instance_ctx *ctx = crypto_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->enc);
	crypto_drop_ahash(&ctx->auth);
	kfree(inst);
}