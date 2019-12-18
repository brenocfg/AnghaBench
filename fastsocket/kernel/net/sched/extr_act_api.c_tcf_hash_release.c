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
struct tcf_hashinfo {int dummy; } ;
struct tcf_common {scalar_t__ tcfc_bindcnt; scalar_t__ tcfc_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcf_hash_destroy (struct tcf_common*,struct tcf_hashinfo*) ; 

int tcf_hash_release(struct tcf_common *p, int bind,
		     struct tcf_hashinfo *hinfo)
{
	int ret = 0;

	if (p) {
		if (bind)
			p->tcfc_bindcnt--;

		p->tcfc_refcnt--;
		if (p->tcfc_bindcnt <= 0 && p->tcfc_refcnt <= 0) {
			tcf_hash_destroy(p, hinfo);
			ret = 1;
		}
	}
	return ret;
}