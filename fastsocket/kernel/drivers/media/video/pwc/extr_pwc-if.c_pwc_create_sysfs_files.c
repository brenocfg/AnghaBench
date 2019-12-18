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
struct video_device {int /*<<< orphan*/  dev; } ;
struct pwc_device {int features; } ;

/* Variables and functions */
 int FEATURE_MOTOR_PANTILT ; 
 int /*<<< orphan*/  PWC_ERROR (char*) ; 
 int /*<<< orphan*/  dev_attr_button ; 
 int /*<<< orphan*/  dev_attr_pan_tilt ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pwc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int pwc_create_sysfs_files(struct video_device *vdev)
{
	struct pwc_device *pdev = video_get_drvdata(vdev);
	int rc;

	rc = device_create_file(&vdev->dev, &dev_attr_button);
	if (rc)
		goto err;
	if (pdev->features & FEATURE_MOTOR_PANTILT) {
		rc = device_create_file(&vdev->dev, &dev_attr_pan_tilt);
		if (rc)
			goto err_button;
	}

	return 0;

err_button:
	device_remove_file(&vdev->dev, &dev_attr_button);
err:
	PWC_ERROR("Could not create sysfs files.\n");
	return rc;
}