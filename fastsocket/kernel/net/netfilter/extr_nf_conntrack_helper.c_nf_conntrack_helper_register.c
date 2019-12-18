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
struct nf_conntrack_helper {scalar_t__ expect_class_max; int /*<<< orphan*/  hnode; int /*<<< orphan*/  name; int /*<<< orphan*/ * expect_policy; int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NF_CT_HELPER_NAME_LEN ; 
 scalar_t__ NF_CT_MAX_EXPECT_CLASSES ; 
 unsigned int helper_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_count ; 
 int /*<<< orphan*/ * nf_ct_helper_hash ; 
 int /*<<< orphan*/  nf_ct_helper_mutex ; 
 int strlen (int /*<<< orphan*/ ) ; 

int nf_conntrack_helper_register(struct nf_conntrack_helper *me)
{
	unsigned int h = helper_hash(&me->tuple);

	BUG_ON(me->expect_policy == NULL);
	BUG_ON(me->expect_class_max >= NF_CT_MAX_EXPECT_CLASSES);
	BUG_ON(strlen(me->name) > NF_CT_HELPER_NAME_LEN - 1);

	mutex_lock(&nf_ct_helper_mutex);
	hlist_add_head_rcu(&me->hnode, &nf_ct_helper_hash[h]);
	nf_ct_helper_count++;
	mutex_unlock(&nf_ct_helper_mutex);

	return 0;
}