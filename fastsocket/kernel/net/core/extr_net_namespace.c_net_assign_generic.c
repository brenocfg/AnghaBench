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
struct net_generic {int len; void** ptr; int /*<<< orphan*/  rcu; } ;
struct net {struct net_generic* gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void***,void***,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct net_generic* net_alloc_generic () ; 
 int /*<<< orphan*/  net_generic_release ; 
 int /*<<< orphan*/  net_mutex ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct net_generic*,struct net_generic*) ; 

int net_assign_generic(struct net *net, int id, void *data)
{
	struct net_generic *ng, *old_ng;

	BUG_ON(!mutex_is_locked(&net_mutex));
	BUG_ON(id == 0);

	ng = old_ng = net->gen;
	if (old_ng->len >= id)
		goto assign;

	ng = net_alloc_generic();
	if (ng == NULL)
		return -ENOMEM;

	/*
	 * Some synchronisation notes:
	 *
	 * The net_generic explores the net->gen array inside rcu
	 * read section. Besides once set the net->gen->ptr[x]
	 * pointer never changes (see rules in netns/generic.h).
	 *
	 * That said, we simply duplicate this array and schedule
	 * the old copy for kfree after a grace period.
	 */

	memcpy(&ng->ptr, &old_ng->ptr, old_ng->len * sizeof(void*));

	rcu_assign_pointer(net->gen, ng);
	call_rcu(&old_ng->rcu, net_generic_release);
assign:
	ng->ptr[id - 1] = data;
	return 0;
}