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
struct usb_stv {int /*<<< orphan*/  camera_name; TYPE_3__* scratch; TYPE_2__* sbuf; int /*<<< orphan*/ ** urb; int /*<<< orphan*/  wq; scalar_t__ streaming; TYPE_1__* frame; int /*<<< orphan*/ * udev; } ;
struct TYPE_6__ {struct usb_stv* data; } ;
struct TYPE_5__ {struct usb_stv* data; } ;
struct TYPE_4__ {void* grabstate; } ;

/* Variables and functions */
 void* FRAME_ERROR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int STV680_NUMSBUF ; 
 int STV680_NUMSCRATCH ; 
 int /*<<< orphan*/  kfree (struct usb_stv*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void usb_stv680_remove_disconnected (struct usb_stv *stv680)
{
	int i;

	stv680->udev = NULL;
	stv680->frame[0].grabstate = FRAME_ERROR;
	stv680->frame[1].grabstate = FRAME_ERROR;
	stv680->streaming = 0;

	wake_up_interruptible (&stv680->wq);

	for (i = 0; i < STV680_NUMSBUF; i++)
		if (stv680->urb[i]) {
			usb_kill_urb (stv680->urb[i]);
			usb_free_urb (stv680->urb[i]);
			stv680->urb[i] = NULL;
			kfree(stv680->sbuf[i].data);
		}
	for (i = 0; i < STV680_NUMSCRATCH; i++)
		kfree(stv680->scratch[i].data);
	PDEBUG (0, "STV(i): %s disconnected", stv680->camera_name);

	/* Free the memory */
	kfree(stv680);
}