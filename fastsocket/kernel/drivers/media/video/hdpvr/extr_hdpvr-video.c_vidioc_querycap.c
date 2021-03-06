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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct hdpvr_device {int /*<<< orphan*/  udev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDPVR_VERSION ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
			   struct v4l2_capability *cap)
{
	struct hdpvr_device *dev = video_drvdata(file);

	strcpy(cap->driver, "hdpvr");
	strcpy(cap->card, "Hauppauge HD PVR");
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->version = HDPVR_VERSION;
	cap->capabilities =     V4L2_CAP_VIDEO_CAPTURE |
				V4L2_CAP_AUDIO         |
				V4L2_CAP_READWRITE;
	return 0;
}