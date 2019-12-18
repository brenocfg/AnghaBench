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
struct cx88_core {int dummy; } ;
struct TYPE_3__ {struct cx88_core* core; } ;
typedef  TYPE_1__ snd_cx88_card_t ;

/* Variables and functions */
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_RISCI2 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int /*<<< orphan*/  MO_AUD_INTMSK ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int PCI_INT_AUDINT ; 
 size_t SRAM_CH25 ; 
 int /*<<< orphan*/  cx88_sram_channel_dump (struct cx88_core*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cx88_sram_channels ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int _cx88_stop_audio_dma(snd_cx88_card_t *chip)
{
	struct cx88_core *core=chip->core;
	dprintk(1, "Stopping audio DMA\n");

	/* stop dma */
	cx_clear(MO_AUD_DMACNTRL, 0x11);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_AUDINT);
	cx_clear(MO_AUD_INTMSK, AUD_INT_OPC_ERR | AUD_INT_DN_SYNC |
				AUD_INT_DN_RISCI2 | AUD_INT_DN_RISCI1);

	if (debug)
		cx88_sram_channel_dump(chip->core, &cx88_sram_channels[SRAM_CH25]);

	return 0;
}