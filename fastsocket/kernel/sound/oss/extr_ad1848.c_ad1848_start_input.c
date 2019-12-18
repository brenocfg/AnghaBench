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
struct TYPE_6__ {int audio_format; int channels; } ;
typedef  TYPE_1__ ad1848_port_info ;
struct TYPE_7__ {int audio_mode; unsigned long xfer_count; int intr_active; scalar_t__ model; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_8__ {int flags; scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
 int AFMT_IMA_ADPCM ; 
 int AFMT_S16_BE ; 
 int AFMT_S16_LE ; 
 int DMA_AUTOMODE ; 
 scalar_t__ MD_1848 ; 
 int PCM_ENABLE_INPUT ; 
 int /*<<< orphan*/  ad_unmute (TYPE_2__*) ; 
 int /*<<< orphan*/  ad_write (TYPE_2__*,int,unsigned char) ; 
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ad1848_start_input(int dev, unsigned long buf, int count, int intrflag)
{
	unsigned long   flags, cnt;
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;
	ad1848_port_info *portc = (ad1848_port_info *) audio_devs[dev]->portc;

	cnt = count;
	if (portc->audio_format == AFMT_IMA_ADPCM)
	{
		cnt /= 4;
	}
	else
	{
		if (portc->audio_format & (AFMT_S16_LE | AFMT_S16_BE))	/* 16 bit data */
			cnt >>= 1;
	}
	if (portc->channels > 1)
		cnt >>= 1;
	cnt--;

	if ((devc->audio_mode & PCM_ENABLE_INPUT) && (audio_devs[dev]->flags & DMA_AUTOMODE) &&
		intrflag &&
		cnt == devc->xfer_count)
	{
		devc->audio_mode |= PCM_ENABLE_INPUT;
		devc->intr_active = 1;
		return;	/*
			 * Auto DMA mode on. No need to react
			 */
	}
	spin_lock_irqsave(&devc->lock,flags);

	if (devc->model == MD_1848)
	{
		  ad_write(devc, 15, (unsigned char) (cnt & 0xff));
		  ad_write(devc, 14, (unsigned char) ((cnt >> 8) & 0xff));
	}
	else
	{
		  ad_write(devc, 31, (unsigned char) (cnt & 0xff));
		  ad_write(devc, 30, (unsigned char) ((cnt >> 8) & 0xff));
	}

	ad_unmute(devc);

	devc->xfer_count = cnt;
	devc->audio_mode |= PCM_ENABLE_INPUT;
	devc->intr_active = 1;
	spin_unlock_irqrestore(&devc->lock,flags);
}