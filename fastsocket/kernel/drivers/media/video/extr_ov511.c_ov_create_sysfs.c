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

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_bridge ; 
 int /*<<< orphan*/  dev_attr_brightness ; 
 int /*<<< orphan*/  dev_attr_contrast ; 
 int /*<<< orphan*/  dev_attr_custom_id ; 
 int /*<<< orphan*/  dev_attr_exposure ; 
 int /*<<< orphan*/  dev_attr_hue ; 
 int /*<<< orphan*/  dev_attr_model ; 
 int /*<<< orphan*/  dev_attr_saturation ; 
 int /*<<< orphan*/  dev_attr_sensor ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov_create_sysfs(struct video_device *vdev)
{
	int rc;

	rc = device_create_file(&vdev->dev, &dev_attr_custom_id);
	if (rc) goto err;
	rc = device_create_file(&vdev->dev, &dev_attr_model);
	if (rc) goto err_id;
	rc = device_create_file(&vdev->dev, &dev_attr_bridge);
	if (rc) goto err_model;
	rc = device_create_file(&vdev->dev, &dev_attr_sensor);
	if (rc) goto err_bridge;
	rc = device_create_file(&vdev->dev, &dev_attr_brightness);
	if (rc) goto err_sensor;
	rc = device_create_file(&vdev->dev, &dev_attr_saturation);
	if (rc) goto err_bright;
	rc = device_create_file(&vdev->dev, &dev_attr_contrast);
	if (rc) goto err_sat;
	rc = device_create_file(&vdev->dev, &dev_attr_hue);
	if (rc) goto err_contrast;
	rc = device_create_file(&vdev->dev, &dev_attr_exposure);
	if (rc) goto err_hue;

	return 0;

err_hue:
	device_remove_file(&vdev->dev, &dev_attr_hue);
err_contrast:
	device_remove_file(&vdev->dev, &dev_attr_contrast);
err_sat:
	device_remove_file(&vdev->dev, &dev_attr_saturation);
err_bright:
	device_remove_file(&vdev->dev, &dev_attr_brightness);
err_sensor:
	device_remove_file(&vdev->dev, &dev_attr_sensor);
err_bridge:
	device_remove_file(&vdev->dev, &dev_attr_bridge);
err_model:
	device_remove_file(&vdev->dev, &dev_attr_model);
err_id:
	device_remove_file(&vdev->dev, &dev_attr_custom_id);
err:
	return rc;
}