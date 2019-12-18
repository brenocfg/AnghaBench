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
struct shash_desc {int dummy; } ;
struct shash_alg {scalar_t__ import; scalar_t__ export; scalar_t__ setkey; } ;
struct crypto_tfm {int /*<<< orphan*/  exit; struct crypto_alg* __crt_alg; } ;
struct crypto_shash {int dummy; } ;
struct crypto_alg {int dummy; } ;
struct crypto_ahash {scalar_t__ reqsize; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 struct shash_alg* __crypto_shash_alg (struct crypto_alg*) ; 
 struct crypto_shash* crypto_create_tfm (struct crypto_alg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_exit_shash_ops_async ; 
 int /*<<< orphan*/  crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_type ; 
 struct crypto_shash** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  shash_async_digest ; 
 int /*<<< orphan*/  shash_async_export ; 
 int /*<<< orphan*/  shash_async_final ; 
 int /*<<< orphan*/  shash_async_finup ; 
 int /*<<< orphan*/  shash_async_import ; 
 int /*<<< orphan*/  shash_async_init ; 
 int /*<<< orphan*/  shash_async_setkey ; 
 int /*<<< orphan*/  shash_async_update ; 

int crypto_init_shash_ops_async(struct crypto_tfm *tfm)
{
	struct crypto_alg *calg = tfm->__crt_alg;
	struct shash_alg *alg = __crypto_shash_alg(calg);
	struct crypto_ahash *crt = __crypto_ahash_cast(tfm);
	struct crypto_shash **ctx = crypto_tfm_ctx(tfm);
	struct crypto_shash *shash;

	if (!crypto_mod_get(calg))
		return -EAGAIN;

	shash = crypto_create_tfm(calg, &crypto_shash_type);
	if (IS_ERR(shash)) {
		crypto_mod_put(calg);
		return PTR_ERR(shash);
	}

	*ctx = shash;
	tfm->exit = crypto_exit_shash_ops_async;

	crt->init = shash_async_init;
	crt->update = shash_async_update;
	crt->final = shash_async_final;
	crt->finup = shash_async_finup;
	crt->digest = shash_async_digest;

	if (alg->setkey)
		crt->setkey = shash_async_setkey;
	if (alg->export)
		crt->export = shash_async_export;
	if (alg->import)
		crt->import = shash_async_import;

	crt->reqsize = sizeof(struct shash_desc) + crypto_shash_descsize(shash);

	return 0;
}