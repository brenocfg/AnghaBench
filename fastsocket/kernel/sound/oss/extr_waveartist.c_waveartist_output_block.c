#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int audio_format; int channels; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_6__ {int audio_mode; unsigned int xfer_count; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_7__ {int flags; scalar_t__ devc; scalar_t__ portc; } ;

/* Variables and functions */
 int AFMT_S16_BE ; 
 int AFMT_S16_LE ; 
 int DEBUG_OUT ; 
 int DMA_AUTOMODE ; 
 int PCM_ENABLE_OUTPUT ; 
 int /*<<< orphan*/  WACMD_OUTPUTSIZE ; 
 TYPE_4__** audio_devs ; 
 int debug_flg ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waveartist_cmd2 (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  waveartist_lock ; 

__attribute__((used)) static void
waveartist_output_block(int dev, unsigned long buf, int __count, int intrflag)
{
	wavnc_port_info	*portc = (wavnc_port_info *) audio_devs[dev]->portc;
	wavnc_info	*devc = (wavnc_info *) audio_devs[dev]->devc;
	unsigned long	flags;
	unsigned int	count = __count; 

	if (debug_flg & DEBUG_OUT)
		printk("waveartist: output block, buf=0x%lx, count=0x%x...\n",
			buf, count);
	/*
	 * 16 bit data
	 */
	if (portc->audio_format & (AFMT_S16_LE | AFMT_S16_BE))
		count >>= 1;

	if (portc->channels > 1)
		count >>= 1;

	count -= 1;

	if (devc->audio_mode & PCM_ENABLE_OUTPUT &&
	    audio_devs[dev]->flags & DMA_AUTOMODE &&
	    intrflag &&
	    count == devc->xfer_count) {
		devc->audio_mode |= PCM_ENABLE_OUTPUT;
		return;	/*
			 * Auto DMA mode on. No need to react
			 */
	}

	spin_lock_irqsave(&waveartist_lock, flags);

	/*
	 * set sample count
	 */
	waveartist_cmd2(devc, WACMD_OUTPUTSIZE, count);

	devc->xfer_count = count;
	devc->audio_mode |= PCM_ENABLE_OUTPUT;

	spin_unlock_irqrestore(&waveartist_lock, flags);
}