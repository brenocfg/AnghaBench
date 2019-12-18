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
struct video_device_shadow {int /*<<< orphan*/ * lock; } ;
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/  debug; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; } ;
struct em28xx {char* name; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  video_debug ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 
 struct video_device_shadow* video_device_shadow_get (struct video_device*) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct em28xx*) ; 

__attribute__((used)) static struct video_device *em28xx_vdev_init(struct em28xx *dev,
					const struct video_device *template,
					const char *type_name)
{
	struct video_device *vfd;
	struct video_device_shadow *shvfd;

	vfd = video_device_alloc();
	if (NULL == vfd)
		return NULL;

	shvfd = video_device_shadow_get(vfd);
	if (NULL == shvfd)
		return NULL;

	*vfd		= *template;
	vfd->v4l2_dev	= &dev->v4l2_dev;
	vfd->release	= video_device_release;
	vfd->debug	= video_debug;
	shvfd->lock	= &dev->lock;

	snprintf(vfd->name, sizeof(vfd->name), "%s %s",
		 dev->name, type_name);

	video_set_drvdata(vfd, dev);
	return vfd;
}