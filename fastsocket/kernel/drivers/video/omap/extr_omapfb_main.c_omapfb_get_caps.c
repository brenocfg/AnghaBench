#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omapfb_device {TYPE_2__* panel; TYPE_1__* ctrl; } ;
struct omapfb_caps {int /*<<< orphan*/  ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_caps ) (TYPE_2__*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_caps ) (int,struct omapfb_caps*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct omapfb_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int,struct omapfb_caps*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void omapfb_get_caps(struct omapfb_device *fbdev, int plane,
				     struct omapfb_caps *caps)
{
	memset(caps, 0, sizeof(*caps));
	fbdev->ctrl->get_caps(plane, caps);
	caps->ctrl |= fbdev->panel->get_caps(fbdev->panel);
}