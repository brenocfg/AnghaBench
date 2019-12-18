#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  open_mode; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_5__ {int /*<<< orphan*/  open_mode; scalar_t__ audio_mode; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_6__ {scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waveartist_halt (int) ; 
 int /*<<< orphan*/  waveartist_lock ; 

__attribute__((used)) static void
waveartist_close(int dev)
{
	wavnc_info	*devc = (wavnc_info *) audio_devs[dev]->devc;
	wavnc_port_info	*portc = (wavnc_port_info *) audio_devs[dev]->portc;
	unsigned long	flags;

	spin_lock_irqsave(&waveartist_lock, flags);

	waveartist_halt(dev);

	devc->audio_mode = 0;
	devc->open_mode &= ~portc->open_mode;
	portc->open_mode = 0;

	spin_unlock_irqrestore(&waveartist_lock, flags);
}