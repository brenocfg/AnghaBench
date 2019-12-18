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
 int CRYPTO_ALG_TESTED ; 
 int /*<<< orphan*/  CRYPTO_MSG_ALG_REQUEST ; 
 int /*<<< orphan*/  ENOENT ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  crypto_is_larval (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_larval_kill (struct crypto_alg*) ; 
 struct crypto_alg* crypto_larval_lookup (char const*,int,int) ; 
 struct crypto_alg* crypto_larval_wait (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int crypto_probing_notify (int /*<<< orphan*/ ,struct crypto_alg*) ; 

struct crypto_alg *crypto_alg_mod_lookup(const char *name, u32 type, u32 mask)
{
	struct crypto_alg *alg;
	struct crypto_alg *larval;
	int ok;

	if (!((type | mask) & CRYPTO_ALG_TESTED)) {
		type |= CRYPTO_ALG_TESTED;
		mask |= CRYPTO_ALG_TESTED;
	}

	larval = crypto_larval_lookup(name, type, mask);
	if (IS_ERR(larval) || !crypto_is_larval(larval))
		return larval;

	ok = crypto_probing_notify(CRYPTO_MSG_ALG_REQUEST, larval);

	if (ok == NOTIFY_STOP)
		alg = crypto_larval_wait(larval);
	else {
		crypto_mod_put(larval);
		alg = ERR_PTR(-ENOENT);
	}
	crypto_larval_kill(larval);
	return alg;
}