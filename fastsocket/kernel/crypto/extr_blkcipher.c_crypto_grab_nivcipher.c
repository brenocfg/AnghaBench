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
struct TYPE_2__ {int /*<<< orphan*/  inst; } ;
struct crypto_skcipher_spawn {TYPE_1__ base; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int PTR_ERR (struct crypto_alg*) ; 
 struct crypto_alg* crypto_alg_mod_lookup (char const*,int,int) ; 
 int crypto_init_spawn (TYPE_1__*,struct crypto_alg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int crypto_skcipher_mask (int) ; 
 int crypto_skcipher_type (int) ; 

__attribute__((used)) static int crypto_grab_nivcipher(struct crypto_skcipher_spawn *spawn,
				const char *name, u32 type, u32 mask)
{
	struct crypto_alg *alg;
	int err;

	type = crypto_skcipher_type(type);
	mask = crypto_skcipher_mask(mask)| CRYPTO_ALG_GENIV;

	alg = crypto_alg_mod_lookup(name, type, mask);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	err = crypto_init_spawn(&spawn->base, alg, spawn->base.inst, mask);
	crypto_mod_put(alg);
	return err;
}