#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int timer_running; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ad1848_info ;
struct TYPE_6__ {scalar_t__ devc; } ;

/* Variables and functions */
 int ad_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_1__*,int,int) ; 
 TYPE_2__** audio_devs ; 
 scalar_t__ current_interval ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ad1848_tmr_restart(int dev)
{
	unsigned long   flags;
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;

	if (current_interval == 0)
		return;

	spin_lock_irqsave(&devc->lock,flags);
	ad_write(devc, 16, ad_read(devc, 16) | 0x40);
	devc->timer_running = 1;
	spin_unlock_irqrestore(&devc->lock,flags);
}