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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  inst; } ;
struct crypto_skcipher_spawn {TYPE_1__ base; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int PTR_ERR (struct crypto_alg*) ; 
 int crypto_init_spawn (TYPE_1__*,struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_alg* crypto_lookup_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_skcipher_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_type (int /*<<< orphan*/ ) ; 

int crypto_grab_skcipher(struct crypto_skcipher_spawn *spawn, const char *name,
			 u32 type, u32 mask)
{
	struct crypto_alg *alg;
	int err;

	type = crypto_skcipher_type(type);
	mask = crypto_skcipher_mask(mask);

	alg = crypto_lookup_skcipher(name, type, mask);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	err = crypto_init_spawn(&spawn->base, alg, spawn->base.inst, mask);
	crypto_mod_put(alg);
	return err;
}