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
struct usb_se401 {int removed; int /*<<< orphan*/  wq; scalar_t__ streaming; TYPE_1__* frame; int /*<<< orphan*/  user; int /*<<< orphan*/  vdev; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {void* grabstate; } ;

/* Variables and functions */
 void* FRAME_ERROR ; 
 struct usb_se401* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_se401_remove_disconnected (struct usb_se401*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void se401_disconnect(struct usb_interface *intf)
{
	struct usb_se401 *se401 = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (se401) {
		video_unregister_device(&se401->vdev);
		if (!se401->user)
			usb_se401_remove_disconnected(se401);
		else {
			se401->frame[0].grabstate = FRAME_ERROR;
			se401->frame[0].grabstate = FRAME_ERROR;

			se401->streaming = 0;

			wake_up_interruptible(&se401->wq);
			se401->removed = 1;
		}
	}
}