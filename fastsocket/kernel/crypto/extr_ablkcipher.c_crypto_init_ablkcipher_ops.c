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
struct crypto_tfm {struct ablkcipher_tfm crt_ablkcipher; TYPE_1__* __crt_alg; } ;
struct ablkcipher_alg {int ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct TYPE_2__ {struct ablkcipher_alg cra_ablkcipher; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  setkey ; 
 int /*<<< orphan*/  skcipher_null_givdecrypt ; 
 int /*<<< orphan*/  skcipher_null_givencrypt ; 

__attribute__((used)) static int crypto_init_ablkcipher_ops(struct crypto_tfm *tfm, u32 type,
				      u32 mask)
{
	struct ablkcipher_alg *alg = &tfm->__crt_alg->cra_ablkcipher;
	struct ablkcipher_tfm *crt = &tfm->crt_ablkcipher;

	if (alg->ivsize > PAGE_SIZE / 8)
		return -EINVAL;

	crt->setkey = setkey;
	crt->encrypt = alg->encrypt;
	crt->decrypt = alg->decrypt;
	if (!alg->ivsize) {
		crt->givencrypt = skcipher_null_givencrypt;
		crt->givdecrypt = skcipher_null_givdecrypt;
	}
	crt->base = __crypto_ablkcipher_cast(tfm);
	crt->ivsize = alg->ivsize;

	return 0;
}