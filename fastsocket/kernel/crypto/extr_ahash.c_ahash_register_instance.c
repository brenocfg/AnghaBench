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
struct crypto_template {int dummy; } ;
struct ahash_instance {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_crypto_instance (struct ahash_instance*) ; 
 int ahash_prepare_alg (int /*<<< orphan*/ *) ; 
 int crypto_register_instance (struct crypto_template*,int /*<<< orphan*/ ) ; 

int ahash_register_instance(struct crypto_template *tmpl,
			    struct ahash_instance *inst)
{
	int err;

	err = ahash_prepare_alg(&inst->alg);
	if (err)
		return err;

	return crypto_register_instance(tmpl, ahash_crypto_instance(inst));
}