#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_event {int /*<<< orphan*/  node; int /*<<< orphan*/  evt_type; } ;
struct scsi_device {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  event_work; int /*<<< orphan*/  event_list; int /*<<< orphan*/  supported_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scsi_event*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdev_evt_send(struct scsi_device *sdev, struct scsi_event *evt)
{
	unsigned long flags;

#if 0
	/* FIXME: currently this check eliminates all media change events
	 * for polled devices.  Need to update to discriminate between AN
	 * and polled events */
	if (!test_bit(evt->evt_type, sdev->supported_events)) {
		kfree(evt);
		return;
	}
#endif

	spin_lock_irqsave(&sdev->list_lock, flags);
	list_add_tail(&evt->node, &sdev->event_list);
	schedule_work(&sdev->event_work);
	spin_unlock_irqrestore(&sdev->list_lock, flags);
}