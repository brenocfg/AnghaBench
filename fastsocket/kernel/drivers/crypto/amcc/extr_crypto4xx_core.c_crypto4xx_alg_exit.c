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
struct crypto4xx_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_free_sa (struct crypto4xx_ctx*) ; 
 int /*<<< orphan*/  crypto4xx_free_state_record (struct crypto4xx_ctx*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void crypto4xx_alg_exit(struct crypto_tfm *tfm)
{
	struct crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto4xx_free_sa(ctx);
	crypto4xx_free_state_record(ctx);
}