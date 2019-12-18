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
struct tcf_proto {struct tc_u_hnode* root; } ;
struct tc_u_knode {int dummy; } ;
struct tc_u_hnode {int refcnt; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ TC_U32_KEY (int /*<<< orphan*/ ) ; 
 int u32_delete_key (struct tcf_proto*,struct tc_u_knode*) ; 
 int /*<<< orphan*/  u32_destroy_hnode (struct tcf_proto*,struct tc_u_hnode*) ; 

__attribute__((used)) static int u32_delete(struct tcf_proto *tp, unsigned long arg)
{
	struct tc_u_hnode *ht = (struct tc_u_hnode*)arg;

	if (ht == NULL)
		return 0;

	if (TC_U32_KEY(ht->handle))
		return u32_delete_key(tp, (struct tc_u_knode*)ht);

	if (tp->root == ht)
		return -EINVAL;

	if (ht->refcnt == 1) {
		ht->refcnt--;
		u32_destroy_hnode(tp, ht);
	} else {
		return -EBUSY;
	}

	return 0;
}