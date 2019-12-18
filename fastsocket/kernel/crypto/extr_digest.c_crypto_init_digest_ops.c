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
struct hash_tfm {int digestsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct digest_alg {int dia_digestsize; scalar_t__ dia_setkey; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct hash_tfm crt_hash; } ;
struct TYPE_2__ {struct digest_alg cra_digest; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  digest ; 
 int /*<<< orphan*/  final ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  nosetkey ; 
 int /*<<< orphan*/  setkey ; 
 int /*<<< orphan*/  update ; 

int crypto_init_digest_ops(struct crypto_tfm *tfm)
{
	struct hash_tfm *ops = &tfm->crt_hash;
	struct digest_alg *dalg = &tfm->__crt_alg->cra_digest;

	if (dalg->dia_digestsize > PAGE_SIZE / 8)
		return -EINVAL;
	
	ops->init	= init;
	ops->update	= update;
	ops->final	= final;
	ops->digest	= digest;
	ops->setkey	= dalg->dia_setkey ? setkey : nosetkey;
	ops->digestsize	= dalg->dia_digestsize;
	
	return 0;
}