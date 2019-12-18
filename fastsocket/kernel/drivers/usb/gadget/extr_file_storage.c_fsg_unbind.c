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
struct usb_request {int /*<<< orphan*/  buf; } ;
struct usb_gadget {int dummy; } ;
struct lun {scalar_t__ registered; int /*<<< orphan*/  dev; } ;
struct fsg_dev {int nluns; scalar_t__ state; int /*<<< orphan*/  ep0; TYPE_1__* buffhds; int /*<<< orphan*/  thread_notifier; struct lun* luns; int /*<<< orphan*/  atomic_bitflags; struct usb_request* ep0req; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  FSG_STATE_EXIT ; 
 scalar_t__ FSG_STATE_TERMINATED ; 
 int NUM_BUFFERS ; 
 int /*<<< orphan*/  REGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_backing_file (struct lun*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_file ; 
 int /*<<< orphan*/  dev_attr_ro ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 struct fsg_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gadget_data (struct usb_gadget*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,struct usb_request*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void /* __init_or_exit */ fsg_unbind(struct usb_gadget *gadget)
{
	struct fsg_dev		*fsg = get_gadget_data(gadget);
	int			i;
	struct lun		*curlun;
	struct usb_request	*req = fsg->ep0req;

	DBG(fsg, "unbind\n");
	clear_bit(REGISTERED, &fsg->atomic_bitflags);

	/* Unregister the sysfs attribute files and the LUNs */
	for (i = 0; i < fsg->nluns; ++i) {
		curlun = &fsg->luns[i];
		if (curlun->registered) {
			device_remove_file(&curlun->dev, &dev_attr_ro);
			device_remove_file(&curlun->dev, &dev_attr_file);
			close_backing_file(curlun);
			device_unregister(&curlun->dev);
			curlun->registered = 0;
		}
	}

	/* If the thread isn't already dead, tell it to exit now */
	if (fsg->state != FSG_STATE_TERMINATED) {
		raise_exception(fsg, FSG_STATE_EXIT);
		wait_for_completion(&fsg->thread_notifier);

		/* The cleanup routine waits for this completion also */
		complete(&fsg->thread_notifier);
	}

	/* Free the data buffers */
	for (i = 0; i < NUM_BUFFERS; ++i)
		kfree(fsg->buffhds[i].buf);

	/* Free the request and buffer for endpoint 0 */
	if (req) {
		kfree(req->buf);
		usb_ep_free_request(fsg->ep0, req);
	}

	set_gadget_data(gadget, NULL);
}