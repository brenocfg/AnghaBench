#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dma; scalar_t__ buf; int /*<<< orphan*/  urb; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma; scalar_t__ buf; int /*<<< orphan*/  urb; } ;
struct mimio {TYPE_3__* idev; TYPE_2__ out; int /*<<< orphan*/  udev; TYPE_1__ in; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; scalar_t__ grab; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIMIO_MAXPAYLOAD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_close_device (scalar_t__) ; 
 int /*<<< orphan*/  input_free_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct mimio*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mimio_dealloc(struct mimio *mimio)
{
	if (mimio == NULL)
		return;

	usb_kill_urb(mimio->in.urb);

	usb_kill_urb(mimio->out.urb);

	if (mimio->idev) {
		input_unregister_device(mimio->idev);
		if (mimio->idev->grab)
			input_close_device(mimio->idev->grab);
		else
			dev_dbg(&mimio->idev->dev, "mimio->idev->grab == NULL"
				" -- didn't call input_close_device\n");
	}

	usb_free_urb(mimio->in.urb);

	usb_free_urb(mimio->out.urb);

	if (mimio->in.buf) {
		usb_buffer_free(mimio->udev, MIMIO_MAXPAYLOAD, mimio->in.buf,
				mimio->in.dma);
	}

	if (mimio->out.buf)
		usb_buffer_free(mimio->udev, MIMIO_MAXPAYLOAD, mimio->out.buf,
				mimio->out.dma);

	if (mimio->idev)
		input_free_device(mimio->idev);

	kfree(mimio);
}