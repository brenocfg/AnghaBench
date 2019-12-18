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
struct aead_tfm {int /*<<< orphan*/  authsize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  base; void* givdecrypt; void* givencrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct aead_tfm crt_aead; } ;
struct aead_alg {int /*<<< orphan*/  maxauthsize; int /*<<< orphan*/  ivsize; scalar_t__ givdecrypt; scalar_t__ givencrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct TYPE_2__ {int cra_flags; struct aead_alg cra_aead; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __crypto_aead_cast (struct crypto_tfm*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* no_givcrypt ; 
 int /*<<< orphan*/  setkey ; 

__attribute__((used)) static int crypto_init_aead_ops(struct crypto_tfm *tfm, u32 type, u32 mask)
{
	struct aead_alg *alg = &tfm->__crt_alg->cra_aead;
	struct aead_tfm *crt = &tfm->crt_aead;

	if (max(alg->maxauthsize, alg->ivsize) > PAGE_SIZE / 8)
		return -EINVAL;

	crt->setkey = tfm->__crt_alg->cra_flags & CRYPTO_ALG_GENIV ?
		      alg->setkey : setkey;
	crt->encrypt = alg->encrypt;
	crt->decrypt = alg->decrypt;
	crt->givencrypt = alg->givencrypt ?: no_givcrypt;
	crt->givdecrypt = alg->givdecrypt ?: no_givcrypt;
	crt->base = __crypto_aead_cast(tfm);
	crt->ivsize = alg->ivsize;
	crt->authsize = alg->maxauthsize;

	return 0;
}