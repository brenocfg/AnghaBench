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
struct matroxfb_driver {void* (* probe ) (struct matrox_fb_info*) ;int /*<<< orphan*/  node; } ;
struct TYPE_4__ {TYPE_2__* next; } ;
struct matrox_fb_info {size_t drivers_count; struct matroxfb_driver** drivers; void** drivers_data; TYPE_1__ next_fb; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 size_t MATROXFB_MAX_FB_DRIVERS ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matroxfb_driver_list ; 
 struct matrox_fb_info* matroxfb_l (TYPE_2__*) ; 
 TYPE_2__ matroxfb_list ; 
 void* stub1 (struct matrox_fb_info*) ; 

int matroxfb_register_driver(struct matroxfb_driver* drv) {
	struct matrox_fb_info* minfo;

	list_add(&drv->node, &matroxfb_driver_list);
	for (minfo = matroxfb_l(matroxfb_list.next);
	     minfo != matroxfb_l(&matroxfb_list);
	     minfo = matroxfb_l(minfo->next_fb.next)) {
		void* p;

		if (minfo->drivers_count == MATROXFB_MAX_FB_DRIVERS)
			continue;
		p = drv->probe(minfo);
		if (p) {
			minfo->drivers_data[minfo->drivers_count] = p;
			minfo->drivers[minfo->drivers_count++] = drv;
		}
	}
	return 0;
}