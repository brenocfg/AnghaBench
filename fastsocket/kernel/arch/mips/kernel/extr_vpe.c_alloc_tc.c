#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tc {int index; int /*<<< orphan*/  list; int /*<<< orphan*/  tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  tc_list_lock; int /*<<< orphan*/  tc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct tc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ vpecontrol ; 

__attribute__((used)) static struct tc *alloc_tc(int index)
{
	struct tc *tc;

	if ((tc = kzalloc(sizeof(struct tc), GFP_KERNEL)) == NULL)
		goto out;

	INIT_LIST_HEAD(&tc->tc);
	tc->index = index;

	spin_lock(&vpecontrol.tc_list_lock);
	list_add_tail(&tc->list, &vpecontrol.tc_list);
	spin_unlock(&vpecontrol.tc_list_lock);

out:
	return tc;
}