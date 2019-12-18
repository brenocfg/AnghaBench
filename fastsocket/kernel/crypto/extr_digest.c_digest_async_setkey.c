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
typedef  int /*<<< orphan*/  u8 ;
struct digest_alg {int (* dia_setkey ) (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int) ;} ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_2__ {struct digest_alg cra_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ahash_tfm (struct crypto_ahash*) ; 
 int stub1 (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int digest_async_setkey(struct crypto_ahash *tfm_async, const u8 *key,
			unsigned int keylen)
{
	struct crypto_tfm    *tfm        = crypto_ahash_tfm(tfm_async);
	struct digest_alg    *dalg       = &tfm->__crt_alg->cra_digest;

	crypto_ahash_clear_flags(tfm_async, CRYPTO_TFM_RES_MASK);
	return dalg->dia_setkey(tfm, key, keylen);
}