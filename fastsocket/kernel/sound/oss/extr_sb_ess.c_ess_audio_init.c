#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct audio_driver {int dummy; } ;
struct TYPE_3__ {int dma16; int dma8; scalar_t__ duplex; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int AFMT_S16_LE ; 
 int DMA_AUTOMODE ; 
 int DMA_DUPLEX ; 
 struct audio_driver ess_audio_driver ; 

struct audio_driver *ess_audio_init
		(sb_devc *devc, int *audio_flags, int *format_mask)
{
	*audio_flags = DMA_AUTOMODE;
	*format_mask |= AFMT_S16_LE;

	if (devc->duplex) {
		int tmp_dma;
		/*
		 * sb_audio_init thinks dma8 is for playback and
		 * dma16 is for record. Not now! So swap them.
		 */
		tmp_dma		= devc->dma16;
		devc->dma16	= devc->dma8;
		devc->dma8	= tmp_dma;

		*audio_flags |= DMA_DUPLEX;
	}

	return &ess_audio_driver;
}