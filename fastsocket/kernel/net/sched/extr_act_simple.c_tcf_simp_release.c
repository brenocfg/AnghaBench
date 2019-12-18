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
struct tcf_defact {scalar_t__ tcf_bindcnt; scalar_t__ tcf_refcnt; int /*<<< orphan*/  common; int /*<<< orphan*/  tcfd_defdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simp_hash_info ; 
 int /*<<< orphan*/  tcf_hash_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcf_simp_release(struct tcf_defact *d, int bind)
{
	int ret = 0;
	if (d) {
		if (bind)
			d->tcf_bindcnt--;
		d->tcf_refcnt--;
		if (d->tcf_bindcnt <= 0 && d->tcf_refcnt <= 0) {
			kfree(d->tcfd_defdata);
			tcf_hash_destroy(&d->common, &simp_hash_info);
			ret = 1;
		}
	}
	return ret;
}