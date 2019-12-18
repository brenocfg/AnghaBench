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
struct cx25821_dev {int dummy; } ;
struct TYPE_3__ {struct cx25821_dev* dev; } ;
typedef  TYPE_1__ snd_cx25821_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_A_INT_MSK ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int AUD_INT_DN_RISCI1 ; 
 int AUD_INT_DN_RISCI2 ; 
 int AUD_INT_DN_SYNC ; 
 int AUD_INT_OPC_ERR ; 
 int FLD_AUD_DST_A_FIFO_EN ; 
 int FLD_AUD_DST_A_RISC_EN ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int PCI_MSK_AUD_INT ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _cx25821_stop_audio_dma(snd_cx25821_card_t * chip)
{
	struct cx25821_dev *dev = chip->dev;

	/* stop dma */
	cx_clear(AUD_INT_DMA_CTL,
		 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);

	/* disable irqs */
	cx_clear(PCI_INT_MSK, PCI_MSK_AUD_INT);
	cx_clear(AUD_A_INT_MSK,
		 AUD_INT_OPC_ERR | AUD_INT_DN_SYNC | AUD_INT_DN_RISCI2 |
		 AUD_INT_DN_RISCI1);

	return 0;
}