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
struct seqiv_ctx {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 struct crypto_ablkcipher* __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 struct seqiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int skcipher_geniv_init (struct crypto_tfm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seqiv_init(struct crypto_tfm *tfm)
{
	struct crypto_ablkcipher *geniv = __crypto_ablkcipher_cast(tfm);
	struct seqiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);

	spin_lock_init(&ctx->lock);

	tfm->crt_ablkcipher.reqsize = sizeof(struct ablkcipher_request);

	return skcipher_geniv_init(tfm);
}