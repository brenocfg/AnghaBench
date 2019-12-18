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
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct async_chainiv_ctx {TYPE_1__ queue; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHAINIV_STATE_INUSE ; 
 struct async_chainiv_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  skcipher_geniv_exit (struct crypto_tfm*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_chainiv_exit(struct crypto_tfm *tfm)
{
	struct async_chainiv_ctx *ctx = crypto_tfm_ctx(tfm);

	BUG_ON(test_bit(CHAINIV_STATE_INUSE, &ctx->state) || ctx->queue.qlen);

	skcipher_geniv_exit(tfm);
}