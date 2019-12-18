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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 struct shash_desc** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kzfree (struct shash_desc*) ; 

__attribute__((used)) static void crypto_exit_shash_ops_compat(struct crypto_tfm *tfm)
{
	struct shash_desc **descp = crypto_tfm_ctx(tfm);
	struct shash_desc *desc = *descp;

	crypto_free_shash(desc->tfm);
	kzfree(desc);
}