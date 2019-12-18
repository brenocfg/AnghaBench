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
typedef  scalar_t__ u32 ;
struct tcf_hashinfo {int dummy; } ;
struct tcf_common {int /*<<< orphan*/  tcfc_refcnt; int /*<<< orphan*/  tcfc_bindcnt; } ;
struct tc_action {struct tcf_common* priv; } ;

/* Variables and functions */
 struct tcf_common* tcf_hash_lookup (scalar_t__,struct tcf_hashinfo*) ; 

struct tcf_common *tcf_hash_check(u32 index, struct tc_action *a, int bind,
				  struct tcf_hashinfo *hinfo)
{
	struct tcf_common *p = NULL;
	if (index && (p = tcf_hash_lookup(index, hinfo)) != NULL) {
		if (bind)
			p->tcfc_bindcnt++;
		p->tcfc_refcnt++;
		a->priv = p;
	}
	return p;
}