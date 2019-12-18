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
struct snd_kctl_event {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct snd_ctl_file {int /*<<< orphan*/  read_lock; TYPE_1__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_kctl_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct snd_kctl_event* snd_kctl_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ctl_empty_read_queue(struct snd_ctl_file * ctl)
{
	unsigned long flags;
	struct snd_kctl_event *cread;
	
	spin_lock_irqsave(&ctl->read_lock, flags);
	while (!list_empty(&ctl->events)) {
		cread = snd_kctl_event(ctl->events.next);
		list_del(&cread->list);
		kfree(cread);
	}
	spin_unlock_irqrestore(&ctl->read_lock, flags);
}