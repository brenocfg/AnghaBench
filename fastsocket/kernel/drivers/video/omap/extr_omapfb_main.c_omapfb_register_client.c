#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* notifier_call ) (struct notifier_block*,unsigned long,void*) ;} ;
struct omapfb_notifier_block {size_t plane_idx; TYPE_3__ nb; void* data; } ;
typedef  scalar_t__ omapfb_notifier_callback_t ;
struct TYPE_5__ {TYPE_1__* ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* bind_client ) (struct omapfb_notifier_block*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int OMAPFB_PLANE_NUM ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int notifier_inited ; 
 int /*<<< orphan*/ * omapfb_client_list ; 
 TYPE_2__* omapfb_dev ; 
 int /*<<< orphan*/  omapfb_init_notifier () ; 
 int /*<<< orphan*/  stub1 (struct omapfb_notifier_block*) ; 

int omapfb_register_client(struct omapfb_notifier_block *omapfb_nb,
				omapfb_notifier_callback_t callback,
				void *callback_data)
{
	int r;

	if ((unsigned)omapfb_nb->plane_idx > OMAPFB_PLANE_NUM)
		return -EINVAL;

	if (!notifier_inited) {
		omapfb_init_notifier();
		notifier_inited = 1;
	}

	omapfb_nb->nb.notifier_call = (int (*)(struct notifier_block *,
					unsigned long, void *))callback;
	omapfb_nb->data = callback_data;
	r = blocking_notifier_chain_register(
				&omapfb_client_list[omapfb_nb->plane_idx],
				&omapfb_nb->nb);
	if (r)
		return r;
	if (omapfb_dev != NULL &&
	    omapfb_dev->ctrl && omapfb_dev->ctrl->bind_client) {
		omapfb_dev->ctrl->bind_client(omapfb_nb);
	}

	return 0;
}