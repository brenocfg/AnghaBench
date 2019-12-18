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
struct matroxfb_driver {int /*<<< orphan*/  (* remove ) (struct matrox_fb_info*,int /*<<< orphan*/ ) ;} ;
struct matrox_fb_info {int drivers_count; int /*<<< orphan*/ * drivers_data; struct matroxfb_driver** drivers; int /*<<< orphan*/  next_fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void matroxfb_unregister_device(struct matrox_fb_info* minfo) {
	int i;

	list_del(&minfo->next_fb);
	for (i = 0; i < minfo->drivers_count; i++) {
		struct matroxfb_driver* drv = minfo->drivers[i];

		if (drv && drv->remove)
			drv->remove(minfo, minfo->drivers_data[i]);
	}
}