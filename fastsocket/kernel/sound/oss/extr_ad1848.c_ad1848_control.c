#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int supported_devices; int supported_rec_devices; int* mixer_reroute; int /*<<< orphan*/  lock; int /*<<< orphan*/  model; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
#define  AD1848_MIXER_REROUTE 129 
#define  AD1848_SET_XTAL 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MD_1845 ; 
 int /*<<< orphan*/  MD_1845_SSCAPE ; 
 int SOUND_MIXER_NONE ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  ad1848_mixer_set (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad_enter_MCE (TYPE_1__*) ; 
 int /*<<< orphan*/  ad_leave_MCE (TYPE_1__*) ; 
 int ad_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_1__*,int,int) ; 
 TYPE_1__* adev_info ; 
 int nr_ad1848_devs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ad1848_control(int cmd, int arg)
{
	ad1848_info *devc;
	unsigned long flags;

	if (nr_ad1848_devs < 1)
		return -ENODEV;

	devc = &adev_info[nr_ad1848_devs - 1];

	switch (cmd)
	{
		case AD1848_SET_XTAL:	/* Change clock frequency of AD1845 (only ) */
			if (devc->model != MD_1845 && devc->model != MD_1845_SSCAPE)
				return -EINVAL;
			spin_lock_irqsave(&devc->lock,flags);
			ad_enter_MCE(devc);
			ad_write(devc, 29, (ad_read(devc, 29) & 0x1f) | (arg << 5));
			ad_leave_MCE(devc);
			spin_unlock_irqrestore(&devc->lock,flags);
			break;

		case AD1848_MIXER_REROUTE:
		{
			int o = (arg >> 8) & 0xff;
			int n = arg & 0xff;

			if (o < 0 || o >= SOUND_MIXER_NRDEVICES)
				return -EINVAL;

			if (!(devc->supported_devices & (1 << o)) &&
			    !(devc->supported_rec_devices & (1 << o)))
				return -EINVAL;

			if (n == SOUND_MIXER_NONE)
			{	/* Just hide this control */
				ad1848_mixer_set(devc, o, 0);	/* Shut up it */
				devc->supported_devices &= ~(1 << o);
				devc->supported_rec_devices &= ~(1 << o);
				break;
			}

			/* Make the mixer control identified by o to appear as n */
			if (n < 0 || n >= SOUND_MIXER_NRDEVICES)
				return -EINVAL;

			devc->mixer_reroute[n] = o;	/* Rename the control */
			if (devc->supported_devices & (1 << o))
				devc->supported_devices |= (1 << n);
			if (devc->supported_rec_devices & (1 << o))
				devc->supported_rec_devices |= (1 << n);

			devc->supported_devices &= ~(1 << o);
			devc->supported_rec_devices &= ~(1 << o);
		}
		break;
	}
	return 0;
}