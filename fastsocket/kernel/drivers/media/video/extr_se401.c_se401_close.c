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
struct video_device {int dummy; } ;
struct usb_se401 {int maxframesize; scalar_t__ user; scalar_t__ streaming; TYPE_2__* frame; TYPE_1__* dev; scalar_t__ removed; int /*<<< orphan*/  fbuf; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  grabstate; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_UNUSED ; 
 int SE401_NUMFRAMES ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_stop_stream (struct usb_se401*) ; 
 int /*<<< orphan*/  usb_se401_remove_disconnected (struct usb_se401*) ; 

__attribute__((used)) static int se401_close(struct file *file)
{
	struct video_device *dev = file->private_data;
	struct usb_se401 *se401 = (struct usb_se401 *)dev;
	int i;

	rvfree(se401->fbuf, se401->maxframesize * SE401_NUMFRAMES);
	if (se401->removed) {
		dev_info(&se401->dev->dev, "device unregistered\n");
		usb_se401_remove_disconnected(se401);
	} else {
		for (i = 0; i < SE401_NUMFRAMES; i++)
			se401->frame[i].grabstate = FRAME_UNUSED;
		if (se401->streaming)
			se401_stop_stream(se401);
		se401->user = 0;
	}
	file->private_data = NULL;
	return 0;
}