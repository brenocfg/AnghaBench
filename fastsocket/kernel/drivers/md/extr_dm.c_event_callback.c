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
struct mapped_device {int /*<<< orphan*/  eventq; int /*<<< orphan*/  event_nr; int /*<<< orphan*/  disk; int /*<<< orphan*/  uevent_lock; int /*<<< orphan*/  uevent_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_send_uevents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uevents ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void event_callback(void *context)
{
	unsigned long flags;
	LIST_HEAD(uevents);
	struct mapped_device *md = (struct mapped_device *) context;

	spin_lock_irqsave(&md->uevent_lock, flags);
	list_splice_init(&md->uevent_list, &uevents);
	spin_unlock_irqrestore(&md->uevent_lock, flags);

	dm_send_uevents(&uevents, &disk_to_dev(md->disk)->kobj);

	atomic_inc(&md->event_nr);
	wake_up(&md->eventq);
}