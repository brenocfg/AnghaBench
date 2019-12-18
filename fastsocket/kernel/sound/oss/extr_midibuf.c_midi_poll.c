#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* outputc ) (int,int) ;} ;
struct TYPE_7__ {int* queue; size_t head; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {scalar_t__ expires; } ;

/* Variables and functions */
 int DATA_AVAIL (TYPE_2__*) ; 
 int MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lock ; 
 TYPE_3__** midi_devs ; 
 TYPE_2__** midi_out_buf ; 
 int /*<<< orphan*/ * midi_sleeper ; 
 int num_midis ; 
 scalar_t__ open_devs ; 
 TYPE_1__ poll_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void midi_poll(unsigned long dummy)
{
	unsigned long   flags;
	int             dev;

	spin_lock_irqsave(&lock, flags);
	if (open_devs)
	{
		for (dev = 0; dev < num_midis; dev++)
			if (midi_devs[dev] != NULL && midi_out_buf[dev] != NULL)
			{
				while (DATA_AVAIL(midi_out_buf[dev]))
				{
					int ok;
					int c = midi_out_buf[dev]->queue[midi_out_buf[dev]->head];

					spin_unlock_irqrestore(&lock,flags);/* Give some time to others */
					ok = midi_devs[dev]->outputc(dev, c);
					spin_lock_irqsave(&lock, flags);
					if (!ok)
						break;
					midi_out_buf[dev]->head = (midi_out_buf[dev]->head + 1) % MAX_QUEUE_SIZE;
					midi_out_buf[dev]->len--;
				}

				if (DATA_AVAIL(midi_out_buf[dev]) < 100)
					wake_up(&midi_sleeper[dev]);
			}
		poll_timer.expires = (1) + jiffies;
		add_timer(&poll_timer);
		/*
		 * Come back later
		 */
	}
	spin_unlock_irqrestore(&lock, flags);
}