#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct crypto_tfm {int dummy; } ;
typedef  struct crypto_tfm crypto_alg ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_GENIV ; 
 int CRYPTO_ALG_TYPE_AEAD ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EAGAIN ; 
 int EINTR ; 
 struct crypto_aead* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 int PTR_ERR (struct crypto_tfm*) ; 
 struct crypto_aead* __crypto_aead_cast (struct crypto_tfm*) ; 
 struct crypto_tfm* __crypto_alloc_tfm (struct crypto_tfm*,int,int) ; 
 struct crypto_tfm* crypto_lookup_aead (char const*,int,int) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_tfm*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

struct crypto_aead *crypto_alloc_aead(const char *alg_name, u32 type, u32 mask)
{
	struct crypto_tfm *tfm;
	int err;

	type &= ~(CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_GENIV);
	type |= CRYPTO_ALG_TYPE_AEAD;
	mask &= ~(CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_GENIV);
	mask |= CRYPTO_ALG_TYPE_MASK;

	for (;;) {
		struct crypto_alg *alg;

		alg = crypto_lookup_aead(alg_name, type, mask);
		if (IS_ERR(alg)) {
			err = PTR_ERR(alg);
			goto err;
		}

		tfm = __crypto_alloc_tfm(alg, type, mask);
		if (!IS_ERR(tfm))
			return __crypto_aead_cast(tfm);

		crypto_mod_put(alg);
		err = PTR_ERR(tfm);

err:
		if (err != -EAGAIN)
			break;
		if (signal_pending(current)) {
			err = -EINTR;
			break;
		}
	}

	return ERR_PTR(err);
}