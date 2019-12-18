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
struct hash_alg {int /*<<< orphan*/  digestsize; } ;
struct ahash_tfm {int /*<<< orphan*/  digestsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct ahash_tfm crt_ahash; } ;
struct TYPE_2__ {struct hash_alg cra_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_async_digest ; 
 int /*<<< orphan*/  hash_async_final ; 
 int /*<<< orphan*/  hash_async_init ; 
 int /*<<< orphan*/  hash_async_setkey ; 
 int /*<<< orphan*/  hash_async_update ; 

__attribute__((used)) static int crypto_init_hash_ops_async(struct crypto_tfm *tfm)
{
	struct ahash_tfm *crt = &tfm->crt_ahash;
	struct hash_alg  *alg = &tfm->__crt_alg->cra_hash;

	crt->init       = hash_async_init;
	crt->update     = hash_async_update;
	crt->final      = hash_async_final;
	crt->digest     = hash_async_digest;
	crt->setkey     = hash_async_setkey;
	crt->digestsize = alg->digestsize;

	return 0;
}