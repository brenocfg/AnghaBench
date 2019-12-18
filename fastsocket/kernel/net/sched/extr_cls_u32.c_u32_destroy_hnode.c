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
struct tcf_proto {struct tc_u_common* data; } ;
struct tc_u_hnode {int refcnt; struct tc_u_hnode* next; } ;
struct tc_u_common {struct tc_u_hnode* hlist; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct tc_u_hnode*) ; 
 int /*<<< orphan*/  u32_clear_hnode (struct tcf_proto*,struct tc_u_hnode*) ; 

__attribute__((used)) static int u32_destroy_hnode(struct tcf_proto *tp, struct tc_u_hnode *ht)
{
	struct tc_u_common *tp_c = tp->data;
	struct tc_u_hnode **hn;

	WARN_ON(ht->refcnt);

	u32_clear_hnode(tp, ht);

	for (hn = &tp_c->hlist; *hn; hn = &(*hn)->next) {
		if (*hn == ht) {
			*hn = ht->next;
			kfree(ht);
			return 0;
		}
	}

	WARN_ON(1);
	return -ENOENT;
}