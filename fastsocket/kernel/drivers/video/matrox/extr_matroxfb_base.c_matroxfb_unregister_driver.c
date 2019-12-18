#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct matroxfb_driver {int /*<<< orphan*/  (* remove ) (struct matrox_fb_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  node; } ;
struct TYPE_4__ {TYPE_2__* next; } ;
struct matrox_fb_info {int drivers_count; int /*<<< orphan*/ * drivers_data; struct matroxfb_driver** drivers; TYPE_1__ next_fb; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct matrox_fb_info* matroxfb_l (TYPE_2__*) ; 
 TYPE_2__ matroxfb_list ; 
 int /*<<< orphan*/  stub1 (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 

void matroxfb_unregister_driver(struct matroxfb_driver* drv) {
	struct matrox_fb_info* minfo;

	list_del(&drv->node);
	for (minfo = matroxfb_l(matroxfb_list.next);
	     minfo != matroxfb_l(&matroxfb_list);
	     minfo = matroxfb_l(minfo->next_fb.next)) {
		int i;

		for (i = 0; i < minfo->drivers_count; ) {
			if (minfo->drivers[i] == drv) {
				if (drv && drv->remove)
					drv->remove(minfo, minfo->drivers_data[i]);
				minfo->drivers[i] = minfo->drivers[--minfo->drivers_count];
				minfo->drivers_data[i] = minfo->drivers_data[minfo->drivers_count];
			} else
				i++;
		}
	}
}