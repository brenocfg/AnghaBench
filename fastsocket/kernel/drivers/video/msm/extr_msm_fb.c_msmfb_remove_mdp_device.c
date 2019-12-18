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
struct device {int dummy; } ;
struct class_interface {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 TYPE_1__* mdp ; 
 int /*<<< orphan*/  msm_panel_driver ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msmfb_remove_mdp_device(struct device *dev,
				struct class_interface *class_intf)
{
	/* might need locking if mulitple mdp devices */
	if (dev != &mdp->dev)
		return;
	platform_driver_unregister(&msm_panel_driver);
	mdp = NULL;
}