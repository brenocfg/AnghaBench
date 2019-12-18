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
struct pcmcia_socket {unsigned int thread_events; int /*<<< orphan*/  dev; int /*<<< orphan*/  skt_mutex; int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; int /*<<< orphan*/  socket; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CS_EVENT_BATTERY_DEAD ; 
 int /*<<< orphan*/  CS_EVENT_BATTERY_LOW ; 
 int /*<<< orphan*/  CS_EVENT_PRI_LOW ; 
 int /*<<< orphan*/  CS_EVENT_READY_CHANGE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 unsigned int SS_READY ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pccard_sysfs_add_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pccard_sysfs_remove_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  send_event (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  socket_detect_change (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int pccardd(void *__skt)
{
	struct pcmcia_socket *skt = __skt;
	int ret;

	skt->thread = current;
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);

	/* register with the device core */
	ret = device_register(&skt->dev);
	if (ret) {
		dev_printk(KERN_WARNING, &skt->dev,
			   "PCMCIA: unable to register socket\n");
		skt->thread = NULL;
		complete(&skt->thread_done);
		return 0;
	}
	ret = pccard_sysfs_add_socket(&skt->dev);
	if (ret)
		dev_warn(&skt->dev, "err %d adding socket attributes\n", ret);

	complete(&skt->thread_done);

	set_freezable();
	for (;;) {
		unsigned long flags;
		unsigned int events;

		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock_irqsave(&skt->thread_lock, flags);
		events = skt->thread_events;
		skt->thread_events = 0;
		spin_unlock_irqrestore(&skt->thread_lock, flags);

		if (events) {
			mutex_lock(&skt->skt_mutex);
			if (events & SS_DETECT)
				socket_detect_change(skt);
			if (events & SS_BATDEAD)
				send_event(skt, CS_EVENT_BATTERY_DEAD, CS_EVENT_PRI_LOW);
			if (events & SS_BATWARN)
				send_event(skt, CS_EVENT_BATTERY_LOW, CS_EVENT_PRI_LOW);
			if (events & SS_READY)
				send_event(skt, CS_EVENT_READY_CHANGE, CS_EVENT_PRI_LOW);
			mutex_unlock(&skt->skt_mutex);
			continue;
		}

		if (kthread_should_stop())
			break;

		schedule();
		try_to_freeze();
	}
	/* make sure we are running before we exit */
	set_current_state(TASK_RUNNING);

	/* remove from the device core */
	pccard_sysfs_remove_socket(&skt->dev);
	device_unregister(&skt->dev);

	return 0;
}