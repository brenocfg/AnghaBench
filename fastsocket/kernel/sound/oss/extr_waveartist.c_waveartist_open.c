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
struct TYPE_4__ {int open_mode; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_5__ {int open_mode; int record_dev; int playback_dev; scalar_t__ audio_mode; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_6__ {scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int OPEN_READ ; 
 int OPEN_WRITE ; 
 TYPE_3__** audio_devs ; 
 int num_audiodevs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waveartist_lock ; 
 int /*<<< orphan*/  waveartist_trigger (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
waveartist_open(int dev, int mode)
{
	wavnc_info	*devc;
	wavnc_port_info	*portc;
	unsigned long	flags;

	if (dev < 0 || dev >= num_audiodevs)
		return -ENXIO;

	devc  = (wavnc_info *) audio_devs[dev]->devc;
	portc = (wavnc_port_info *) audio_devs[dev]->portc;

	spin_lock_irqsave(&waveartist_lock, flags);
	if (portc->open_mode || (devc->open_mode & mode)) {
		spin_unlock_irqrestore(&waveartist_lock, flags);
		return -EBUSY;
	}

	devc->audio_mode  = 0;
	devc->open_mode  |= mode;
	portc->open_mode  = mode;
	waveartist_trigger(dev, 0);

	if (mode & OPEN_READ)
		devc->record_dev = dev;
	if (mode & OPEN_WRITE)
		devc->playback_dev = dev;
	spin_unlock_irqrestore(&waveartist_lock, flags);

	return 0;
}