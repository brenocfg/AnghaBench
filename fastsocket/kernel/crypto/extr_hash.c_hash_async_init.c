#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct hash_alg {int (* init ) (struct hash_desc*) ;} ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; struct crypto_tfm* tfm; } ;
struct ahash_request {TYPE_2__ base; } ;
struct TYPE_3__ {struct hash_alg cra_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_hash_cast (struct crypto_tfm*) ; 
 int stub1 (struct hash_desc*) ; 

__attribute__((used)) static int hash_async_init(struct ahash_request *req)
{
	struct crypto_tfm *tfm = req->base.tfm;
	struct hash_alg   *alg = &tfm->__crt_alg->cra_hash;
	struct hash_desc  desc = {
		.tfm = __crypto_hash_cast(tfm),
		.flags = req->base.flags,
	};

	return alg->init(&desc);
}