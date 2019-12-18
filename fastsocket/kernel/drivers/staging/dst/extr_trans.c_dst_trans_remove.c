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
struct dst_trans {struct dst_node* n; } ;
struct dst_node {int /*<<< orphan*/  trans_lock; } ;

/* Variables and functions */
 int dst_trans_remove_nolock (struct dst_trans*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dst_trans_remove(struct dst_trans *t)
{
	int ret;
	struct dst_node *n = t->n;

	mutex_lock(&n->trans_lock);
	ret = dst_trans_remove_nolock(t);
	mutex_unlock(&n->trans_lock);

	return ret;
}