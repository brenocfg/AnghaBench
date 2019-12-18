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
struct usb_se401 {TYPE_2__* scratch; TYPE_1__* sbuf; int /*<<< orphan*/ ** urb; scalar_t__ streaming; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int SE401_NUMSBUF ; 
 int SE401_NUMSCRATCH ; 
 int /*<<< orphan*/  SE401_REQ_CAMERA_POWER ; 
 int /*<<< orphan*/  SE401_REQ_LED_CONTROL ; 
 int /*<<< orphan*/  SE401_REQ_STOP_CONTINUOUS_CAPTURE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  se401_sndctrl (int,struct usb_se401*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int se401_stop_stream(struct usb_se401 *se401)
{
	int i;

	if (!se401->streaming || !se401->dev)
		return 1;

	se401->streaming = 0;

	se401_sndctrl(1, se401, SE401_REQ_STOP_CONTINUOUS_CAPTURE, 0, NULL, 0);

	se401_sndctrl(1, se401, SE401_REQ_LED_CONTROL, 0, NULL, 0);
	se401_sndctrl(1, se401, SE401_REQ_CAMERA_POWER, 0, NULL, 0);

	for (i = 0; i < SE401_NUMSBUF; i++)
		if (se401->urb[i]) {
			usb_kill_urb(se401->urb[i]);
			usb_free_urb(se401->urb[i]);
			se401->urb[i] = NULL;
			kfree(se401->sbuf[i].data);
		}
	for (i = 0; i < SE401_NUMSCRATCH; i++) {
		kfree(se401->scratch[i].data);
		se401->scratch[i].data = NULL;
	}

	return 0;
}