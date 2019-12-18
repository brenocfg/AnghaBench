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
struct tcf_proto {int dummy; } ;
struct tc_u_knode {struct tc_u_knode* next; int /*<<< orphan*/  handle; struct tc_u_hnode* ht_up; } ;
struct tc_u_hnode {struct tc_u_knode** ht; } ;

/* Variables and functions */
 size_t TC_U32_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 int /*<<< orphan*/  u32_destroy_key (struct tcf_proto*,struct tc_u_knode*) ; 

__attribute__((used)) static int u32_delete_key(struct tcf_proto *tp, struct tc_u_knode* key)
{
	struct tc_u_knode **kp;
	struct tc_u_hnode *ht = key->ht_up;

	if (ht) {
		for (kp = &ht->ht[TC_U32_HASH(key->handle)]; *kp; kp = &(*kp)->next) {
			if (*kp == key) {
				tcf_tree_lock(tp);
				*kp = key->next;
				tcf_tree_unlock(tp);

				u32_destroy_key(tp, key);
				return 0;
			}
		}
	}
	WARN_ON(1);
	return 0;
}