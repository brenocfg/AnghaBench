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
struct TYPE_2__ {int /*<<< orphan*/  reqsize; struct crypto_aead* base; } ;
struct crypto_tfm {TYPE_1__ crt_aead; scalar_t__ __crt_alg; } ;
struct crypto_instance {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_reqsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_aead* crypto_spawn_aead (int /*<<< orphan*/ ) ; 

int aead_geniv_init(struct crypto_tfm *tfm)
{
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct crypto_aead *aead;

	aead = crypto_spawn_aead(crypto_instance_ctx(inst));
	if (IS_ERR(aead))
		return PTR_ERR(aead);

	tfm->crt_aead.base = aead;
	tfm->crt_aead.reqsize += crypto_aead_reqsize(aead);

	return 0;
}