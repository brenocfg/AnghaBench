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
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_ahash {scalar_t__ import; scalar_t__ export; scalar_t__ setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct ahash_alg {scalar_t__ import; scalar_t__ export; scalar_t__ setkey; int /*<<< orphan*/  digest; scalar_t__ finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ahash_def_finup ; 
 scalar_t__ ahash_no_export ; 
 scalar_t__ ahash_no_import ; 
 scalar_t__ ahash_nosetkey ; 
 struct ahash_alg* crypto_ahash_alg (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_type ; 
 int crypto_init_shash_ops_async (struct crypto_tfm*) ; 

__attribute__((used)) static int crypto_ahash_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_ahash *hash = __crypto_ahash_cast(tfm);
	struct ahash_alg *alg = crypto_ahash_alg(hash);

	hash->setkey = ahash_nosetkey;
	hash->export = ahash_no_export;
	hash->import = ahash_no_import;

	if (tfm->__crt_alg->cra_type != &crypto_ahash_type)
		return crypto_init_shash_ops_async(tfm);

	hash->init = alg->init;
	hash->update = alg->update;
	hash->final = alg->final;
	hash->finup = alg->finup ?: ahash_def_finup;
	hash->digest = alg->digest;

	if (alg->setkey)
		hash->setkey = alg->setkey;
	if (alg->export)
		hash->export = alg->export;
	if (alg->import)
		hash->import = alg->import;

	return 0;
}