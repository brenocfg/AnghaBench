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
struct TYPE_5__ {int /*<<< orphan*/  open_mode; } ;
typedef  TYPE_1__ ad1848_port_info ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  open_mode; scalar_t__ audio_mode; scalar_t__ intr_active; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_7__ {scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1848_halt (int) ; 
 int /*<<< orphan*/  ad_unmute (TYPE_2__*) ; 
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ad1848_close(int dev)
{
	unsigned long   flags;
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;
	ad1848_port_info *portc = (ad1848_port_info *) audio_devs[dev]->portc;

	DEB(printk("ad1848_close(void)\n"));

	devc->intr_active = 0;
	ad1848_halt(dev);

	spin_lock_irqsave(&devc->lock,flags);

	devc->audio_mode = 0;
	devc->open_mode &= ~portc->open_mode;
	portc->open_mode = 0;

	ad_unmute(devc);
	spin_unlock_irqrestore(&devc->lock,flags);
}