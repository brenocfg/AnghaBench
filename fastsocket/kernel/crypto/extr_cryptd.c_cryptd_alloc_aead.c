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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* __crt_alg; } ;
struct crypto_aead {TYPE_2__ base; } ;
struct cryptd_aead {int dummy; } ;
struct TYPE_3__ {scalar_t__ cra_module; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  EINVAL ; 
 struct cryptd_aead* ERR_CAST (struct crypto_aead*) ; 
 struct cryptd_aead* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 scalar_t__ THIS_MODULE ; 
 struct cryptd_aead* __cryptd_aead_cast (struct crypto_aead*) ; 
 struct crypto_aead* crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_aead*) ; 
 int snprintf (char*,int,char*,char const*) ; 

struct cryptd_aead *cryptd_alloc_aead(const char *alg_name,
						  u32 type, u32 mask)
{
	char cryptd_alg_name[CRYPTO_MAX_ALG_NAME];
	struct crypto_aead *tfm;

	if (snprintf(cryptd_alg_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)", alg_name) >= CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-EINVAL);
	tfm = crypto_alloc_aead(cryptd_alg_name, type, mask);
	if (IS_ERR(tfm))
		return ERR_CAST(tfm);
	if (tfm->base.__crt_alg->cra_module != THIS_MODULE) {
		crypto_free_aead(tfm);
		return ERR_PTR(-EINVAL);
	}
	return __cryptd_aead_cast(tfm);
}