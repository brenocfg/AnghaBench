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
struct aead_tfm {int /*<<< orphan*/  authsize; scalar_t__ ivsize; int /*<<< orphan*/  base; int /*<<< orphan*/  givdecrypt; int /*<<< orphan*/  givencrypt; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_tfm {struct aead_tfm crt_aead; TYPE_1__* __crt_alg; } ;
struct aead_alg {int /*<<< orphan*/  maxauthsize; scalar_t__ ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct TYPE_2__ {struct aead_alg cra_aead; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __crypto_aead_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  aead_null_givdecrypt ; 
 int /*<<< orphan*/  aead_null_givencrypt ; 
 int max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setkey ; 

__attribute__((used)) static int crypto_init_nivaead_ops(struct crypto_tfm *tfm, u32 type, u32 mask)
{
	struct aead_alg *alg = &tfm->__crt_alg->cra_aead;
	struct aead_tfm *crt = &tfm->crt_aead;

	if (max(alg->maxauthsize, alg->ivsize) > PAGE_SIZE / 8)
		return -EINVAL;

	crt->setkey = setkey;
	crt->encrypt = alg->encrypt;
	crt->decrypt = alg->decrypt;
	if (!alg->ivsize) {
		crt->givencrypt = aead_null_givencrypt;
		crt->givdecrypt = aead_null_givdecrypt;
	}
	crt->base = __crypto_aead_cast(tfm);
	crt->ivsize = alg->ivsize;
	crt->authsize = alg->maxauthsize;

	return 0;
}