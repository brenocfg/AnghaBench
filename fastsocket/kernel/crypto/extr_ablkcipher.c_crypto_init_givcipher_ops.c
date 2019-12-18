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
typedef  int /*<<< orphan*/  u32 ;
struct ablkcipher_tfm {int ivsize; int /*<<< orphan*/  base; int /*<<< orphan*/  givdecrypt; int /*<<< orphan*/  givencrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct ablkcipher_tfm crt_ablkcipher; } ;
struct ablkcipher_alg {int ivsize; scalar_t__ givdecrypt; int /*<<< orphan*/  givencrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct TYPE_2__ {int cra_flags; struct ablkcipher_alg cra_ablkcipher; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  no_givdecrypt ; 
 int /*<<< orphan*/  setkey ; 

__attribute__((used)) static int crypto_init_givcipher_ops(struct crypto_tfm *tfm, u32 type,
				      u32 mask)
{
	struct ablkcipher_alg *alg = &tfm->__crt_alg->cra_ablkcipher;
	struct ablkcipher_tfm *crt = &tfm->crt_ablkcipher;

	if (alg->ivsize > PAGE_SIZE / 8)
		return -EINVAL;

	crt->setkey = tfm->__crt_alg->cra_flags & CRYPTO_ALG_GENIV ?
		      alg->setkey : setkey;
	crt->encrypt = alg->encrypt;
	crt->decrypt = alg->decrypt;
	crt->givencrypt = alg->givencrypt;
	crt->givdecrypt = alg->givdecrypt ?: no_givdecrypt;
	crt->base = __crypto_ablkcipher_cast(tfm);
	crt->ivsize = alg->ivsize;

	return 0;
}