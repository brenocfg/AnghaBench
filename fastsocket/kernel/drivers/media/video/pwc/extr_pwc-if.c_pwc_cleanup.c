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
struct pwc_device {scalar_t__ button_dev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_remove_sysfs_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwc_cleanup(struct pwc_device *pdev)
{
	pwc_remove_sysfs_files(pdev->vdev);
	video_unregister_device(pdev->vdev);

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	if (pdev->button_dev)
		input_unregister_device(pdev->button_dev);
#endif

	kfree(pdev);
}