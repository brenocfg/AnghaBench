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
 int /*<<< orphan*/  dev_attr_decoding_errors ; 
 int /*<<< orphan*/  dev_attr_frames_read ; 
 int /*<<< orphan*/  dev_attr_frames_total ; 
 int /*<<< orphan*/  dev_attr_in_use ; 
 int /*<<< orphan*/  dev_attr_model ; 
 int /*<<< orphan*/  dev_attr_packets_dropped ; 
 int /*<<< orphan*/  dev_attr_palette ; 
 int /*<<< orphan*/  dev_attr_streaming ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stv680_remove_sysfs_files(struct video_device *vdev)
{
	device_remove_file(&vdev->dev, &dev_attr_model);
	device_remove_file(&vdev->dev, &dev_attr_in_use);
	device_remove_file(&vdev->dev, &dev_attr_streaming);
	device_remove_file(&vdev->dev, &dev_attr_palette);
	device_remove_file(&vdev->dev, &dev_attr_frames_total);
	device_remove_file(&vdev->dev, &dev_attr_frames_read);
	device_remove_file(&vdev->dev, &dev_attr_packets_dropped);
	device_remove_file(&vdev->dev, &dev_attr_decoding_errors);
}