#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct TYPE_3__ {scalar_t__ has_audio; } ;
struct em28xx {size_t model; scalar_t__ tuner_type; TYPE_1__ audio_mode; scalar_t__ vbi_dev; int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_VERSION_CODE ; 
 scalar_t__ TUNER_ABSENT ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_SLICED_VBI_CAPTURE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 TYPE_2__* em28xx_boards ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct em28xx_fh      *fh  = priv;
	struct em28xx         *dev = fh->dev;

	strlcpy(cap->driver, "em28xx", sizeof(cap->driver));
	strlcpy(cap->card, em28xx_boards[dev->model].name, sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	cap->version = EM28XX_VERSION_CODE;

	cap->capabilities =
			V4L2_CAP_SLICED_VBI_CAPTURE |
			V4L2_CAP_VIDEO_CAPTURE |
			V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;

	if (dev->vbi_dev)
		cap->capabilities |= V4L2_CAP_VBI_CAPTURE;

	if (dev->audio_mode.has_audio)
		cap->capabilities |= V4L2_CAP_AUDIO;

	if (dev->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;

	return 0;
}