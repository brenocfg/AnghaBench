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
struct eseqiv_request_ctx {int dummy; } ;
struct eseqiv_ctx {unsigned int reqoff; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 struct crypto_ablkcipher* __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 unsigned long crypto_ablkcipher_alignmask (struct crypto_ablkcipher*) ; 
 struct eseqiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int crypto_tfm_ctx_alignment () ; 
 int skcipher_geniv_init (struct crypto_tfm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eseqiv_init(struct crypto_tfm *tfm)
{
	struct crypto_ablkcipher *geniv = __crypto_ablkcipher_cast(tfm);
	struct eseqiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);
	unsigned long alignmask;
	unsigned int reqsize;

	spin_lock_init(&ctx->lock);

	alignmask = crypto_tfm_ctx_alignment() - 1;
	reqsize = sizeof(struct eseqiv_request_ctx);

	if (alignmask & reqsize) {
		alignmask &= reqsize;
		alignmask--;
	}

	alignmask = ~alignmask;
	alignmask &= crypto_ablkcipher_alignmask(geniv);

	reqsize += alignmask;
	reqsize += crypto_ablkcipher_ivsize(geniv);
	reqsize = ALIGN(reqsize, crypto_tfm_ctx_alignment());

	ctx->reqoff = reqsize - sizeof(struct eseqiv_request_ctx);

	tfm->crt_ablkcipher.reqsize = reqsize +
				      sizeof(struct ablkcipher_request);

	return skcipher_geniv_init(tfm);
}