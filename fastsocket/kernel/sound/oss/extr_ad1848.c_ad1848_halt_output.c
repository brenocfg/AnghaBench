#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  audio_mode; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_10__ {TYPE_1__* dmap_out; scalar_t__ devc; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM_ENABLE_OUTPUT ; 
 int /*<<< orphan*/  ad_mute (TYPE_2__*) ; 
 int ad_read (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_2__*,int,int) ; 
 TYPE_4__** audio_devs ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_Status (TYPE_2__*) ; 
 int /*<<< orphan*/  isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ad1848_halt_output(int dev)
{
	ad1848_info *devc = (ad1848_info *) audio_devs[dev]->devc;
	unsigned long flags;

	if (!(ad_read(devc, 9) & 0x01))
		return;		/* Playback not enabled */

	spin_lock_irqsave(&devc->lock,flags);

	ad_mute(devc);
	{
		int             tmout;

		if(!isa_dma_bridge_buggy)
		        disable_dma(audio_devs[dev]->dmap_out->dma);

		for (tmout = 0; tmout < 100000; tmout++)
			if (ad_read(devc, 11) & 0x10)
				break;
		ad_write(devc, 9, ad_read(devc, 9) & ~0x01);	/* Stop playback */

		if(!isa_dma_bridge_buggy)
		       enable_dma(audio_devs[dev]->dmap_out->dma);

		devc->audio_mode &= ~PCM_ENABLE_OUTPUT;
	}

	outb((0), io_Status(devc));	/* Clear interrupt status */
	outb((0), io_Status(devc));	/* Clear interrupt status */

	devc->audio_mode &= ~PCM_ENABLE_OUTPUT;

	spin_unlock_irqrestore(&devc->lock,flags);
}