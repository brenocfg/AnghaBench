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
struct TYPE_2__ {int /*<<< orphan*/  ivsize; } ;
struct crypto_alg {int cra_flags; TYPE_1__ cra_aead; int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CRYPTO_ALG_TESTED ; 
 int /*<<< orphan*/  ENOENT ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_aead_type ; 
 struct crypto_alg* crypto_alg_mod_lookup (char const*,int,int) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_nivaead_default (struct crypto_alg*,int,int) ; 

__attribute__((used)) static struct crypto_alg *crypto_lookup_aead(const char *name, u32 type,
					     u32 mask)
{
	struct crypto_alg *alg;

	alg = crypto_alg_mod_lookup(name, type, mask);
	if (IS_ERR(alg))
		return alg;

	if (alg->cra_type == &crypto_aead_type)
		return alg;

	if (!alg->cra_aead.ivsize)
		return alg;

	crypto_mod_put(alg);
	alg = crypto_alg_mod_lookup(name, type | CRYPTO_ALG_TESTED,
				    mask & ~CRYPTO_ALG_TESTED);
	if (IS_ERR(alg))
		return alg;

	if (alg->cra_type == &crypto_aead_type) {
		if ((alg->cra_flags ^ type ^ ~mask) & CRYPTO_ALG_TESTED) {
			crypto_mod_put(alg);
			alg = ERR_PTR(-ENOENT);
		}
		return alg;
	}

	BUG_ON(!alg->cra_aead.ivsize);

	return ERR_PTR(crypto_nivaead_default(alg, type, mask));
}