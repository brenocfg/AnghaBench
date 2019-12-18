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
struct crypto_alg {int /*<<< orphan*/  (* cra_destroy ) (struct crypto_alg*) ;int /*<<< orphan*/  cra_refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypto_alg*) ; 

__attribute__((used)) static inline void crypto_alg_put(struct crypto_alg *alg)
{
	if (atomic_dec_and_test(&alg->cra_refcnt) && alg->cra_destroy)
		alg->cra_destroy(alg);
}