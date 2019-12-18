#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {char* name; TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_6__ {TYPE_1__* udev; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GO7007_BOARD_HAS_TUNER ; 
 int /*<<< orphan*/  KERNEL_VERSION (int /*<<< orphan*/ ,int,int) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 TYPE_3__* dev ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	strlcpy(cap->driver, "go7007", sizeof(cap->driver));
	strlcpy(cap->card, go->name, sizeof(cap->card));
#if 0
	strlcpy(cap->bus_info, dev_name(&dev->udev->dev), sizeof(cap->bus_info));
#endif

	cap->version = KERNEL_VERSION(0, 9, 8);

	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE |
			    V4L2_CAP_STREAMING; /* | V4L2_CAP_AUDIO; */

	if (go->board_info->flags & GO7007_BOARD_HAS_TUNER)
		cap->capabilities |= V4L2_CAP_TUNER;

	return 0;
}