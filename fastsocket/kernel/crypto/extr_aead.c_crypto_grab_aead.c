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
typedef  int u32 ;
struct crypto_alg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inst; } ;
struct crypto_aead_spawn {TYPE_1__ base; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int CRYPTO_ALG_TYPE_AEAD ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int PTR_ERR (struct crypto_alg*) ; 
 int crypto_init_spawn (TYPE_1__*,struct crypto_alg*,int /*<<< orphan*/ ,int) ; 
 struct crypto_alg* crypto_lookup_aead (char const*,int,int) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 

int crypto_grab_aead(struct crypto_aead_spawn *spawn, const char *name,
		     u32 type, u32 mask)
{
	struct crypto_alg *alg;
	int err;

	type &= ~(CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_GENIV);
	type |= CRYPTO_ALG_TYPE_AEAD;
	mask &= ~(CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_GENIV);
	mask |= CRYPTO_ALG_TYPE_MASK;

	alg = crypto_lookup_aead(name, type, mask);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	err = crypto_init_spawn(&spawn->base, alg, spawn->base.inst, mask);
	crypto_mod_put(alg);
	return err;
}