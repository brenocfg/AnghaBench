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
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; struct vnode* vp; } ;

/* Variables and functions */
 int ENOENT ; 
 int MAX_NSPACE_ITEMS ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nspace_handler_lock ; 
 TYPE_1__* nspace_items ; 

int
get_nspace_item_status(struct vnode *vp, int32_t *status)
{
	int i;

	lck_mtx_lock(&nspace_handler_lock);
	for(i=0; i < MAX_NSPACE_ITEMS; i++) {
		if (nspace_items[i].vp == vp) {
			break;
		}
	}

	if (i >= MAX_NSPACE_ITEMS) {
		lck_mtx_unlock(&nspace_handler_lock);
		return ENOENT;
	}

	*status = nspace_items[i].flags;
	lck_mtx_unlock(&nspace_handler_lock);
	return 0;
}