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
struct usb_se401 {struct usb_se401* height; struct usb_se401* width; int /*<<< orphan*/  camera_name; TYPE_3__* dev; int /*<<< orphan*/ * inturb; TYPE_2__* scratch; TYPE_1__* sbuf; int /*<<< orphan*/ ** urb; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct usb_se401* data; } ;
struct TYPE_4__ {struct usb_se401* data; } ;

/* Variables and functions */
 int SE401_NUMSBUF ; 
 int SE401_NUMSCRATCH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_se401*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_se401_remove_disconnected(struct usb_se401 *se401)
{
	int i;

	se401->dev = NULL;

	for (i = 0; i < SE401_NUMSBUF; i++)
		if (se401->urb[i]) {
			usb_kill_urb(se401->urb[i]);
			usb_free_urb(se401->urb[i]);
			se401->urb[i] = NULL;
			kfree(se401->sbuf[i].data);
		}

	for (i = 0; i < SE401_NUMSCRATCH; i++)
		kfree(se401->scratch[i].data);

	if (se401->inturb) {
		usb_kill_urb(se401->inturb);
		usb_free_urb(se401->inturb);
	}
	dev_info(&se401->dev->dev, "%s disconnected", se401->camera_name);

	/* Free the memory */
	kfree(se401->width);
	kfree(se401->height);
	kfree(se401);
}