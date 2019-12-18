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
struct vpe {int minor; int /*<<< orphan*/  notify; int /*<<< orphan*/  list; int /*<<< orphan*/  tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpe_list_lock; int /*<<< orphan*/  vpe_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct vpe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ vpecontrol ; 

__attribute__((used)) static struct vpe *alloc_vpe(int minor)
{
	struct vpe *v;

	if ((v = kzalloc(sizeof(struct vpe), GFP_KERNEL)) == NULL)
		return NULL;

	INIT_LIST_HEAD(&v->tc);
	spin_lock(&vpecontrol.vpe_list_lock);
	list_add_tail(&v->list, &vpecontrol.vpe_list);
	spin_unlock(&vpecontrol.vpe_list_lock);

	INIT_LIST_HEAD(&v->notify);
	v->minor = minor;

	return v;
}