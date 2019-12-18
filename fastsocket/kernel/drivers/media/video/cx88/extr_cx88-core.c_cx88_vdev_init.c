#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * v4l2_dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* name; } ;
struct cx88_core {char* name; TYPE_1__ board; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,char*) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 

struct video_device *cx88_vdev_init(struct cx88_core *core,
				    struct pci_dev *pci,
				    struct video_device *template,
				    char *type)
{
	struct video_device *vfd;

	vfd = video_device_alloc();
	if (NULL == vfd)
		return NULL;
	*vfd = *template;
	vfd->v4l2_dev = &core->v4l2_dev;
	vfd->parent = &pci->dev;
	vfd->release = video_device_release;
	snprintf(vfd->name, sizeof(vfd->name), "%s %s (%s)",
		 core->name, type, core->board.name);
	return vfd;
}