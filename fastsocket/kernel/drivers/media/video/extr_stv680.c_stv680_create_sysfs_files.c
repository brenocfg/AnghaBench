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
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_attr_decoding_errors ; 
 int /*<<< orphan*/  dev_attr_frames_read ; 
 int /*<<< orphan*/  dev_attr_frames_total ; 
 int /*<<< orphan*/  dev_attr_in_use ; 
 int /*<<< orphan*/  dev_attr_model ; 
 int /*<<< orphan*/  dev_attr_packets_dropped ; 
 int /*<<< orphan*/  dev_attr_palette ; 
 int /*<<< orphan*/  dev_attr_streaming ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stv680_create_sysfs_files(struct video_device *vdev)
{
	int rc;

	rc = device_create_file(&vdev->dev, &dev_attr_model);
	if (rc) goto err;
	rc = device_create_file(&vdev->dev, &dev_attr_in_use);
	if (rc) goto err_model;
	rc = device_create_file(&vdev->dev, &dev_attr_streaming);
	if (rc) goto err_inuse;
	rc = device_create_file(&vdev->dev, &dev_attr_palette);
	if (rc) goto err_stream;
	rc = device_create_file(&vdev->dev, &dev_attr_frames_total);
	if (rc) goto err_pal;
	rc = device_create_file(&vdev->dev, &dev_attr_frames_read);
	if (rc) goto err_framtot;
	rc = device_create_file(&vdev->dev, &dev_attr_packets_dropped);
	if (rc) goto err_framread;
	rc = device_create_file(&vdev->dev, &dev_attr_decoding_errors);
	if (rc) goto err_dropped;

	return 0;

err_dropped:
	device_remove_file(&vdev->dev, &dev_attr_packets_dropped);
err_framread:
	device_remove_file(&vdev->dev, &dev_attr_frames_read);
err_framtot:
	device_remove_file(&vdev->dev, &dev_attr_frames_total);
err_pal:
	device_remove_file(&vdev->dev, &dev_attr_palette);
err_stream:
	device_remove_file(&vdev->dev, &dev_attr_streaming);
err_inuse:
	device_remove_file(&vdev->dev, &dev_attr_in_use);
err_model:
	device_remove_file(&vdev->dev, &dev_attr_model);
err:
	PDEBUG(0, "STV(e): Could not create sysfs files");
	return rc;
}