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
struct wahc {size_t nep_buffer_size; int /*<<< orphan*/  notifs_queued; int /*<<< orphan*/  nep_buffer; TYPE_1__* usb_iface; } ;
struct wa_notif_work {size_t size; int /*<<< orphan*/  work; int /*<<< orphan*/  data; int /*<<< orphan*/  wa; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct wa_notif_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wa_get (struct wahc*) ; 
 int /*<<< orphan*/  wa_notif_dispatch ; 
 int /*<<< orphan*/  wusbd ; 

__attribute__((used)) static int wa_nep_queue(struct wahc *wa, size_t size)
{
	int result = 0;
	struct device *dev = &wa->usb_iface->dev;
	struct wa_notif_work *nw;

	/* dev_fnstart(dev, "(wa %p, size %zu)\n", wa, size); */
	BUG_ON(size > wa->nep_buffer_size);
	if (size == 0)
		goto out;
	if (atomic_read(&wa->notifs_queued) > 200) {
		if (printk_ratelimit())
			dev_err(dev, "Too many notifications queued, "
				"throttling back\n");
		goto out;
	}
	nw = kzalloc(sizeof(*nw) + size, GFP_ATOMIC);
	if (nw == NULL) {
		if (printk_ratelimit())
			dev_err(dev, "No memory to queue notification\n");
		goto out;
	}
	INIT_WORK(&nw->work, wa_notif_dispatch);
	nw->wa = wa_get(wa);
	nw->size = size;
	memcpy(nw->data, wa->nep_buffer, size);
	atomic_inc(&wa->notifs_queued);		/* Throttling ctl */
	queue_work(wusbd, &nw->work);
out:
	/* dev_fnend(dev, "(wa %p, size %zu) = result\n", wa, size, result); */
	return result;
}