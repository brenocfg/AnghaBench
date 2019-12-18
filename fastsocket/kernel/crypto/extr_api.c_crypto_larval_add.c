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
struct crypto_alg {int /*<<< orphan*/  cra_list; int /*<<< orphan*/  cra_refcnt; } ;
struct crypto_larval {struct crypto_alg alg; } ;

/* Variables and functions */
 struct crypto_alg* ERR_CAST (struct crypto_larval*) ; 
 scalar_t__ IS_ERR (struct crypto_larval*) ; 
 struct crypto_alg* __crypto_alg_lookup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_alg_list ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 scalar_t__ crypto_is_larval (struct crypto_alg*) ; 
 struct crypto_larval* crypto_larval_alloc (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_alg* crypto_larval_wait (struct crypto_alg*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct crypto_larval*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct crypto_alg *crypto_larval_add(const char *name, u32 type,
					    u32 mask)
{
	struct crypto_alg *alg;
	struct crypto_larval *larval;

	larval = crypto_larval_alloc(name, type, mask);
	if (IS_ERR(larval))
		return ERR_CAST(larval);

	atomic_set(&larval->alg.cra_refcnt, 2);

	down_write(&crypto_alg_sem);
	alg = __crypto_alg_lookup(name, type, mask);
	if (!alg) {
		alg = &larval->alg;
		list_add(&alg->cra_list, &crypto_alg_list);
	}
	up_write(&crypto_alg_sem);

	if (alg != &larval->alg) {
		kfree(larval);
		if (crypto_is_larval(alg))
			alg = crypto_larval_wait(alg);
	}

	return alg;
}