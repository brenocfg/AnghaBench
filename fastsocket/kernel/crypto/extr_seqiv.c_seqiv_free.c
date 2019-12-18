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
struct TYPE_2__ {int cra_flags; } ;
struct crypto_instance {TYPE_1__ alg; } ;

/* Variables and functions */
 int CRYPTO_ALG_TYPE_AEAD ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  aead_geniv_free (struct crypto_instance*) ; 
 int /*<<< orphan*/  crypto_put_default_rng () ; 
 int /*<<< orphan*/  skcipher_geniv_free (struct crypto_instance*) ; 

__attribute__((used)) static void seqiv_free(struct crypto_instance *inst)
{
	if ((inst->alg.cra_flags ^ CRYPTO_ALG_TYPE_AEAD) & CRYPTO_ALG_TYPE_MASK)
		skcipher_geniv_free(inst);
	else
		aead_geniv_free(inst);
	crypto_put_default_rng();
}