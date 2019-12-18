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
struct xfrm_state {struct ah_data* data; } ;
struct ah_data {int /*<<< orphan*/  tfm; struct ah_data* work_icv; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ah_data*) ; 

__attribute__((used)) static void ah6_destroy(struct xfrm_state *x)
{
	struct ah_data *ahp = x->data;

	if (!ahp)
		return;

	kfree(ahp->work_icv);
	crypto_free_hash(ahp->tfm);
	kfree(ahp);
}