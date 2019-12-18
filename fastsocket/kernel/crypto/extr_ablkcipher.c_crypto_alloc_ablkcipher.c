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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_tfm {int dummy; } ;
typedef  struct crypto_tfm crypto_alg ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 struct crypto_ablkcipher* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 int PTR_ERR (struct crypto_tfm*) ; 
 struct crypto_ablkcipher* __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 struct crypto_tfm* __crypto_alloc_tfm (struct crypto_tfm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_lookup_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_skcipher_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

struct crypto_ablkcipher *crypto_alloc_ablkcipher(const char *alg_name,
						  u32 type, u32 mask)
{
	struct crypto_tfm *tfm;
	int err;

	type = crypto_skcipher_type(type);
	mask = crypto_skcipher_mask(mask);

	for (;;) {
		struct crypto_alg *alg;

		alg = crypto_lookup_skcipher(alg_name, type, mask);
		if (IS_ERR(alg)) {
			err = PTR_ERR(alg);
			goto err;
		}

		tfm = __crypto_alloc_tfm(alg, type, mask);
		if (!IS_ERR(tfm))
			return __crypto_ablkcipher_cast(tfm);

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