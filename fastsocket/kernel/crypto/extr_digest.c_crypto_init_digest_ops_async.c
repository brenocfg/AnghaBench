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
struct digest_alg {int dia_digestsize; scalar_t__ dia_setkey; } ;
struct ahash_tfm {int digestsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct ahash_tfm crt_ahash; } ;
struct TYPE_2__ {struct digest_alg cra_digest; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  digest_async_digest ; 
 int /*<<< orphan*/  digest_async_final ; 
 int /*<<< orphan*/  digest_async_init ; 
 int /*<<< orphan*/  digest_async_nosetkey ; 
 int /*<<< orphan*/  digest_async_setkey ; 
 int /*<<< orphan*/  digest_async_update ; 

int crypto_init_digest_ops_async(struct crypto_tfm *tfm)
{
	struct ahash_tfm  *crt  = &tfm->crt_ahash;
	struct digest_alg *dalg = &tfm->__crt_alg->cra_digest;

	if (dalg->dia_digestsize > PAGE_SIZE / 8)
		return -EINVAL;

	crt->init       = digest_async_init;
	crt->update     = digest_async_update;
	crt->final      = digest_async_final;
	crt->digest     = digest_async_digest;
	crt->setkey     = dalg->dia_setkey ? digest_async_setkey :
						digest_async_nosetkey;
	crt->digestsize = dalg->dia_digestsize;

	return 0;
}