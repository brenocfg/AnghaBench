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
struct chainiv_ctx {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int chainiv_init_common (struct crypto_tfm*) ; 
 struct chainiv_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chainiv_init(struct crypto_tfm *tfm)
{
	struct chainiv_ctx *ctx = crypto_tfm_ctx(tfm);

	spin_lock_init(&ctx->lock);

	return chainiv_init_common(tfm);
}