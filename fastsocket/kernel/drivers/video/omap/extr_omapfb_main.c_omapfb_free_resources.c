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
struct TYPE_4__ {int region_cnt; } ;
struct omapfb_device {int /*<<< orphan*/  dev; TYPE_2__* panel; int /*<<< orphan*/ * fb_info; TYPE_1__ mem_desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* disable ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAPFB_ACTIVE 128 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 int /*<<< orphan*/  ctrl_cleanup (struct omapfb_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_set_update_mode (struct omapfb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_unregister_sysfs (struct omapfb_device*) ; 
 int /*<<< orphan*/  planes_cleanup (struct omapfb_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omapfb_free_resources(struct omapfb_device *fbdev, int state)
{
	int i;

	switch (state) {
	case OMAPFB_ACTIVE:
		for (i = 0; i < fbdev->mem_desc.region_cnt; i++)
			unregister_framebuffer(fbdev->fb_info[i]);
	case 7:
		omapfb_unregister_sysfs(fbdev);
	case 6:
		fbdev->panel->disable(fbdev->panel);
	case 5:
		omapfb_set_update_mode(fbdev, OMAPFB_UPDATE_DISABLED);
	case 4:
		planes_cleanup(fbdev);
	case 3:
		ctrl_cleanup(fbdev);
	case 2:
		fbdev->panel->cleanup(fbdev->panel);
	case 1:
		dev_set_drvdata(fbdev->dev, NULL);
		kfree(fbdev);
	case 0:
		/* nothing to free */
		break;
	default:
		BUG();
	}
}