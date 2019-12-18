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
struct crypto_tfm {TYPE_1__ crt_aead; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 struct crypto_aead* __crypto_aead_cast (struct crypto_tfm*) ; 
 int aead_geniv_init (struct crypto_tfm*) ; 
 struct seqiv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seqiv_aead_init(struct crypto_tfm *tfm)
{
	struct crypto_aead *geniv = __crypto_aead_cast(tfm);
	struct seqiv_ctx *ctx = crypto_aead_ctx(geniv);

	spin_lock_init(&ctx->lock);

	tfm->crt_aead.reqsize = sizeof(struct aead_request);

	return aead_geniv_init(tfm);
}