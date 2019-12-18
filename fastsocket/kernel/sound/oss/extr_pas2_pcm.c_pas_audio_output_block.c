#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; TYPE_1__* dmap_out; } ;
struct TYPE_3__ {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int DMA_AUTOMODE ; 
 int /*<<< orphan*/  PCM_DAC ; 
 TYPE_2__** audio_devs ; 
 int /*<<< orphan*/  pas_lock ; 
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 
 unsigned long pcm_count ; 
 int /*<<< orphan*/  pcm_mode ; 
 int /*<<< orphan*/  printk (char*,unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pas_audio_output_block(int dev, unsigned long buf, int count,
		       int intrflag)
{
	unsigned long   flags, cnt;

	DEB(printk("pas2_pcm.c: static void pas_audio_output_block(char *buf = %P, int count = %X)\n", buf, count));

	cnt = count;
	if (audio_devs[dev]->dmap_out->dma > 3)
		cnt >>= 1;

	if (audio_devs[dev]->flags & DMA_AUTOMODE &&
	    intrflag &&
	    cnt == pcm_count)
		return;

	spin_lock_irqsave(&pas_lock, flags);

	pas_write(pas_read(0xF8A) & ~0x40,
		  0xF8A);

	/* DMAbuf_start_dma (dev, buf, count, DMA_MODE_WRITE); */

	if (audio_devs[dev]->dmap_out->dma > 3)
		count >>= 1;

	if (count != pcm_count)
	{
		pas_write(pas_read(0x0B8A) & ~0x80, 0x0B8A);
		pas_write(0x40 | 0x30 | 0x04, 0x138B);
		pas_write(count & 0xff, 0x1389);
		pas_write((count >> 8) & 0xff, 0x1389);
		pas_write(pas_read(0x0B8A) | 0x80, 0x0B8A);

		pcm_count = count;
	}
	pas_write(pas_read(0x0B8A) | 0x80 | 0x40, 0x0B8A);
#ifdef NO_TRIGGER
	pas_write(pas_read(0xF8A) | 0x40 | 0x10, 0xF8A);
#endif

	pcm_mode = PCM_DAC;

	spin_unlock_irqrestore(&pas_lock, flags);
}