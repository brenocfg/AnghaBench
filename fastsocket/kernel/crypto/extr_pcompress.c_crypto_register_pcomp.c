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
struct crypto_alg {int /*<<< orphan*/  cra_flags; int /*<<< orphan*/ * cra_type; } ;
struct pcomp_alg {struct crypto_alg base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_PCOMPRESS ; 
 int /*<<< orphan*/  crypto_pcomp_type ; 
 int crypto_register_alg (struct crypto_alg*) ; 

int crypto_register_pcomp(struct pcomp_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	base->cra_type = &crypto_pcomp_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_PCOMPRESS;

	return crypto_register_alg(base);
}