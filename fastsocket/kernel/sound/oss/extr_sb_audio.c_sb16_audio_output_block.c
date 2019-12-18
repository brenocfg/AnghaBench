#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long bits; int intr_active; int intr_active_16; int speed; int channels; int /*<<< orphan*/  lock; scalar_t__ fullduplex; void* irq_mode_16; void* irq_mode; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
 unsigned long AFMT_S16_LE ; 
 unsigned long AFMT_U8 ; 
 void* IMODE_OUTPUT ; 
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  sb_dsp_command (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sb16_audio_output_block(int dev, unsigned long buf, int count,
			int intrflag)
{
	unsigned long   flags, cnt;
	sb_devc        *devc = audio_devs[dev]->devc;
	unsigned long   bits;

	if (!devc->fullduplex || devc->bits == AFMT_S16_LE)
	{
		devc->irq_mode = IMODE_OUTPUT;
		devc->intr_active = 1;
	}
	else
	{
		devc->irq_mode_16 = IMODE_OUTPUT;
		devc->intr_active_16 = 1;
	}

	/* save value */
	spin_lock_irqsave(&devc->lock, flags);
	bits = devc->bits;
	if (devc->fullduplex)
		devc->bits = (devc->bits == AFMT_S16_LE) ?
			AFMT_U8 : AFMT_S16_LE;
	spin_unlock_irqrestore(&devc->lock, flags);

	cnt = count;
	if (devc->bits == AFMT_S16_LE)
		cnt >>= 1;
	cnt--;

	spin_lock_irqsave(&devc->lock, flags);

	/* DMAbuf_start_dma (dev, buf, count, DMA_MODE_WRITE); */

	sb_dsp_command(devc, 0x41);
	sb_dsp_command(devc, (unsigned char) ((devc->speed >> 8) & 0xff));
	sb_dsp_command(devc, (unsigned char) (devc->speed & 0xff));

	sb_dsp_command(devc, (devc->bits == AFMT_S16_LE ? 0xb6 : 0xc6));
	sb_dsp_command(devc, ((devc->channels == 2 ? 0x20 : 0) +
			      (devc->bits == AFMT_S16_LE ? 0x10 : 0)));
	sb_dsp_command(devc, (unsigned char) (cnt & 0xff));
	sb_dsp_command(devc, (unsigned char) (cnt >> 8));

	/* restore real value after all programming */
	devc->bits = bits;
	spin_unlock_irqrestore(&devc->lock, flags);
}