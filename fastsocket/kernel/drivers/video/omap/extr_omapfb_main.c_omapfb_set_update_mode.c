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
struct omapfb_device {TYPE_1__* ctrl; } ;
typedef  enum omapfb_update_mode { ____Placeholder_omapfb_update_mode } omapfb_update_mode ;
struct TYPE_2__ {int (* set_update_mode ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 int stub1 (int) ; 

__attribute__((used)) static int omapfb_set_update_mode(struct omapfb_device *fbdev,
				   enum omapfb_update_mode mode)
{
	int r;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->set_update_mode(mode);
	omapfb_rqueue_unlock(fbdev);

	return r;
}