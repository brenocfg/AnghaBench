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
struct poseidon {int /*<<< orphan*/  udev; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *fh,
			struct v4l2_capability *cap)
{
	struct front_face *front = fh;
	struct poseidon *p = front->pd;

	logs(front);

	strcpy(cap->driver, "tele-video");
	strcpy(cap->card, "Telegent Poseidon");
	usb_make_path(p->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->version = KERNEL_VERSION(0, 0, 1);
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
				V4L2_CAP_AUDIO | V4L2_CAP_STREAMING |
				V4L2_CAP_READWRITE | V4L2_CAP_VBI_CAPTURE;
	return 0;
}