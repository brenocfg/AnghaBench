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
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_DEAD ; 
 int CRYPTO_ALG_LARVAL ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 int /*<<< orphan*/  ENOENT ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct crypto_alg* crypto_alg_lookup (char const*,int,int) ; 
 scalar_t__ crypto_is_larval (struct crypto_alg*) ; 
 struct crypto_alg* crypto_larval_add (char const*,int,int) ; 
 struct crypto_alg* crypto_larval_wait (struct crypto_alg*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

struct crypto_alg *crypto_larval_lookup(const char *name, u32 type, u32 mask)
{
	struct crypto_alg *alg;

	if (!name)
		return ERR_PTR(-ENOENT);

	mask &= ~(CRYPTO_ALG_LARVAL | CRYPTO_ALG_DEAD);
	type &= mask;

	alg = crypto_alg_lookup(name, type, mask);
	if (!alg) {
		request_module("%s", name);

		if (!((type ^ CRYPTO_ALG_NEED_FALLBACK) & mask &
		      CRYPTO_ALG_NEED_FALLBACK))
			request_module("%s-all", name);

		alg = crypto_alg_lookup(name, type, mask);
	}

	if (alg)
		return crypto_is_larval(alg) ? crypto_larval_wait(alg) : alg;

	return crypto_larval_add(name, type, mask);
}