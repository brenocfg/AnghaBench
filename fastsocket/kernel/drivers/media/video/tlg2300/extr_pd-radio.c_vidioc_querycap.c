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
struct file {struct poseidon* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
			struct v4l2_capability *v)
{
	struct poseidon *p = file->private_data;

	strlcpy(v->driver, "tele-radio", sizeof(v->driver));
	strlcpy(v->card, "Telegent Poseidon", sizeof(v->card));
	usb_make_path(p->udev, v->bus_info, sizeof(v->bus_info));
	v->version = KERNEL_VERSION(0, 0, 1);
	v->capabilities = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	return 0;
}