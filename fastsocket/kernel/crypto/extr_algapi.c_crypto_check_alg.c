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
struct crypto_alg {int cra_alignmask; int cra_blocksize; scalar_t__ cra_priority; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int crypto_set_driver_name (struct crypto_alg*) ; 

__attribute__((used)) static int crypto_check_alg(struct crypto_alg *alg)
{
	if (alg->cra_alignmask & (alg->cra_alignmask + 1))
		return -EINVAL;

	if (alg->cra_blocksize > PAGE_SIZE / 8)
		return -EINVAL;

	if (alg->cra_priority < 0)
		return -EINVAL;

	return crypto_set_driver_name(alg);
}