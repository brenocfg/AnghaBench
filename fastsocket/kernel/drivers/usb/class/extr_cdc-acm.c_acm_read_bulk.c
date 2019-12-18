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
struct urb {int status; int /*<<< orphan*/  actual_length; struct acm_ru* context; } ;
struct acm_ru {int /*<<< orphan*/  list; struct acm_rb* buffer; struct acm* instance; } ;
struct acm_rb {int /*<<< orphan*/  list; int /*<<< orphan*/  size; } ;
struct acm {int /*<<< orphan*/  urb_task; int /*<<< orphan*/  susp_count; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  spare_read_bufs; int /*<<< orphan*/  spare_read_urbs; int /*<<< orphan*/  filled_read_bufs; int /*<<< orphan*/  processing; TYPE_1__* data; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_READY (struct acm*) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acm_read_bulk(struct urb *urb)
{
	struct acm_rb *buf;
	struct acm_ru *rcv = urb->context;
	struct acm *acm = rcv->instance;
	int status = urb->status;

	dbg("Entering acm_read_bulk with status %d", status);

	if (!ACM_READY(acm)) {
		dev_dbg(&acm->data->dev, "Aborting, acm not ready");
		return;
	}
	usb_mark_last_busy(acm->dev);

	if (status)
		dev_dbg(&acm->data->dev, "bulk rx status %d\n", status);

	buf = rcv->buffer;
	buf->size = urb->actual_length;

	if (likely(status == 0)) {
		spin_lock(&acm->read_lock);
		acm->processing++;
		list_add_tail(&rcv->list, &acm->spare_read_urbs);
		list_add_tail(&buf->list, &acm->filled_read_bufs);
		spin_unlock(&acm->read_lock);
	} else {
		/* we drop the buffer due to an error */
		spin_lock(&acm->read_lock);
		list_add_tail(&rcv->list, &acm->spare_read_urbs);
		list_add(&buf->list, &acm->spare_read_bufs);
		spin_unlock(&acm->read_lock);
		/* nevertheless the tasklet must be kicked unconditionally
		so the queue cannot dry up */
	}
	if (likely(!acm->susp_count))
		tasklet_schedule(&acm->urb_task);
}