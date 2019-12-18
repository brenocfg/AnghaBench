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
struct platform_device {int dummy; } ;
struct omapfb_device {int state; } ;
typedef  enum omapfb_state { ____Placeholder_omapfb_state } omapfb_state ;

/* Variables and functions */
 int OMAPFB_DISABLED ; 
 int /*<<< orphan*/  omapfb_free_resources (struct omapfb_device*,int) ; 
 struct omapfb_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int omapfb_remove(struct platform_device *pdev)
{
	struct omapfb_device *fbdev = platform_get_drvdata(pdev);
	enum omapfb_state saved_state = fbdev->state;

	/* FIXME: wait till completion of pending events */

	fbdev->state = OMAPFB_DISABLED;
	omapfb_free_resources(fbdev, saved_state);

	return 0;
}