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
struct hash_tfm {int /*<<< orphan*/  digestsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct hash_alg {int /*<<< orphan*/  digestsize; int /*<<< orphan*/  digest; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct hash_tfm crt_hash; } ;
struct TYPE_2__ {struct hash_alg cra_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_setkey ; 

__attribute__((used)) static int crypto_init_hash_ops_sync(struct crypto_tfm *tfm)
{
	struct hash_tfm *crt = &tfm->crt_hash;
	struct hash_alg *alg = &tfm->__crt_alg->cra_hash;

	crt->init       = alg->init;
	crt->update     = alg->update;
	crt->final      = alg->final;
	crt->digest     = alg->digest;
	crt->setkey     = hash_setkey;
	crt->digestsize = alg->digestsize;

	return 0;
}