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
struct vme_dma_list {int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct vme_bridge {int (* dma_list_empty ) (struct vme_dma_list*) ;} ;
struct TYPE_2__ {struct vme_bridge* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct vme_dma_list*) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int stub1 (struct vme_dma_list*) ; 

int vme_dma_list_free(struct vme_dma_list *list)
{
	struct vme_bridge *bridge = list->parent->parent;
	int retval;

	if (bridge->dma_list_empty == NULL) {
		printk("Emptying of Link Lists not supported\n");
		return -EINVAL;
	}

	if (mutex_trylock(&(list->mtx))) {
		printk("Link List in use\n");
		return -EINVAL;
	}

	/*
	 * Empty out all of the entries from the dma list. We need to go to the
	 * low level driver as dma entries are driver specific.
	 */
	retval = bridge->dma_list_empty(list);
	if (retval) {
		printk("Unable to empty link-list entries\n");
		mutex_unlock(&(list->mtx));
		return retval;
	}
	mutex_unlock(&(list->mtx));
	kfree(list);

	return retval;
}