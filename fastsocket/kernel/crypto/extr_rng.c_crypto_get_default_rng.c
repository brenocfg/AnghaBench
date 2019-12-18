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
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_rng*) ; 
 int PTR_ERR (struct crypto_rng*) ; 
 struct crypto_rng* crypto_alloc_rng (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_rng* crypto_default_rng ; 
 int /*<<< orphan*/  crypto_default_rng_lock ; 
 int /*<<< orphan*/  crypto_default_rng_refcnt ; 
 int /*<<< orphan*/  crypto_free_rng (struct crypto_rng*) ; 
 int crypto_rng_reset (struct crypto_rng*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_rng_seedsize (struct crypto_rng*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int crypto_get_default_rng(void)
{
	struct crypto_rng *rng;
	int err;

	mutex_lock(&crypto_default_rng_lock);
	if (!crypto_default_rng) {
		rng = crypto_alloc_rng("stdrng", 0, 0);
		err = PTR_ERR(rng);
		if (IS_ERR(rng))
			goto unlock;

		err = crypto_rng_reset(rng, NULL, crypto_rng_seedsize(rng));
		if (err) {
			crypto_free_rng(rng);
			goto unlock;
		}

		crypto_default_rng = rng;
	}

	crypto_default_rng_refcnt++;
	err = 0;

unlock:
	mutex_unlock(&crypto_default_rng_lock);

	return err;
}