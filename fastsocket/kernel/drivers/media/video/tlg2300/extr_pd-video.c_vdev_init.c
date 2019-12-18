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
struct video_device {int minor; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; } ;
struct poseidon {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct poseidon*) ; 

struct video_device *vdev_init(struct poseidon *pd, struct video_device *tmp)
{
	struct video_device *vfd;

	vfd = video_device_alloc();
	if (vfd == NULL)
		return NULL;
	*vfd		= *tmp;
	vfd->minor	= -1;
	vfd->v4l2_dev	= &pd->v4l2_dev;
	/*vfd->parent	= &(pd->udev->dev); */
	vfd->release	= video_device_release;
	video_set_drvdata(vfd, pd);
	return vfd;
}