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
struct shash_alg {int /*<<< orphan*/  base; } ;
struct crypto_shash_spawn {int /*<<< orphan*/  base; } ;
struct crypto_instance {int dummy; } ;

/* Variables and functions */
 int crypto_init_spawn2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct crypto_instance*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_type ; 

int crypto_init_shash_spawn(struct crypto_shash_spawn *spawn,
			    struct shash_alg *alg,
			    struct crypto_instance *inst)
{
	return crypto_init_spawn2(&spawn->base, &alg->base, inst,
				  &crypto_shash_type);
}