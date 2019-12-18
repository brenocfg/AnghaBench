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
struct w9966_dev {int /*<<< orphan*/  pdev; int /*<<< orphan*/  pport; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE1284_MODE_COMPAT ; 
 int /*<<< orphan*/  W9966_STATE_PDEV ; 
 int /*<<< orphan*/  W9966_STATE_VDEV ; 
 int /*<<< orphan*/  parport_negotiate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 scalar_t__ w9966_getState (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w9966_pdev_claim (struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_pdev_release (struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_setState (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w9966_term(struct w9966_dev* cam)
{
// Unregister from v4l
	if (w9966_getState(cam, W9966_STATE_VDEV, W9966_STATE_VDEV)) {
		video_unregister_device(&cam->vdev);
		w9966_setState(cam, W9966_STATE_VDEV, 0);
	}

// Terminate from IEEE1284 mode and release pdev block
	if (w9966_getState(cam, W9966_STATE_PDEV, W9966_STATE_PDEV)) {
		w9966_pdev_claim(cam);
		parport_negotiate(cam->pport, IEEE1284_MODE_COMPAT);
		w9966_pdev_release(cam);
	}

// Unregister from parport
	if (w9966_getState(cam, W9966_STATE_PDEV, W9966_STATE_PDEV)) {
		parport_unregister_device(cam->pdev);
		w9966_setState(cam, W9966_STATE_PDEV, 0);
	}
}