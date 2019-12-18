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
struct vme_bridge {int (* dma_list_exec ) (struct vme_dma_list*) ;} ;
struct TYPE_2__ {struct vme_bridge* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int stub1 (struct vme_dma_list*) ; 

int vme_dma_list_exec(struct vme_dma_list *list)
{
	struct vme_bridge *bridge = list->parent->parent;
	int retval;

	if (bridge->dma_list_exec == NULL) {
		printk("Link List DMA execution not supported\n");
		return -EINVAL;
	}

	mutex_lock(&(list->mtx));

	retval = bridge->dma_list_exec(list);

	mutex_unlock(&(list->mtx));

	return retval;
}