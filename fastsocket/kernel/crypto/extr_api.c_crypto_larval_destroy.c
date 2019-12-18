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
struct crypto_larval {scalar_t__ adult; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  crypto_is_larval (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct crypto_larval*) ; 

__attribute__((used)) static void crypto_larval_destroy(struct crypto_alg *alg)
{
	struct crypto_larval *larval = (void *)alg;

	BUG_ON(!crypto_is_larval(alg));
	if (larval->adult)
		crypto_mod_put(larval->adult);
	kfree(larval);
}