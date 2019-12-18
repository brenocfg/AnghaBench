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
typedef  int u32 ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct cryptd_ablkcipher {int dummy; } ;
struct TYPE_2__ {scalar_t__ cra_module; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int CRYPTO_ALG_TYPE_BLKCIPHER ; 
 int CRYPTO_ALG_TYPE_BLKCIPHER_MASK ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  EINVAL ; 
 struct cryptd_ablkcipher* ERR_CAST (struct crypto_tfm*) ; 
 struct cryptd_ablkcipher* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 scalar_t__ THIS_MODULE ; 
 struct cryptd_ablkcipher* __cryptd_ablkcipher_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 struct crypto_tfm* crypto_alloc_base (char*,int,int) ; 
 int /*<<< orphan*/  crypto_free_tfm (struct crypto_tfm*) ; 
 int snprintf (char*,int,char*,char const*) ; 

struct cryptd_ablkcipher *cryptd_alloc_ablkcipher(const char *alg_name,
						  u32 type, u32 mask)
{
	char cryptd_alg_name[CRYPTO_MAX_ALG_NAME];
	struct crypto_tfm *tfm;

	if (snprintf(cryptd_alg_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)", alg_name) >= CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-EINVAL);
	type &= ~(CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_GENIV);
	type |= CRYPTO_ALG_TYPE_BLKCIPHER;
	mask &= ~CRYPTO_ALG_TYPE_MASK;
	mask |= (CRYPTO_ALG_GENIV | CRYPTO_ALG_TYPE_BLKCIPHER_MASK);
	tfm = crypto_alloc_base(cryptd_alg_name, type, mask);
	if (IS_ERR(tfm))
		return ERR_CAST(tfm);
	if (tfm->__crt_alg->cra_module != THIS_MODULE) {
		crypto_free_tfm(tfm);
		return ERR_PTR(-EINVAL);
	}

	return __cryptd_ablkcipher_cast(__crypto_ablkcipher_cast(tfm));
}