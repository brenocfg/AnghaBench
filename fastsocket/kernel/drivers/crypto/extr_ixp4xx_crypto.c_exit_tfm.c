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
struct ixp_ctx {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct ixp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_sa_dir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exit_tfm(struct crypto_tfm *tfm)
{
	struct ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	free_sa_dir(&ctx->encrypt);
	free_sa_dir(&ctx->decrypt);
}