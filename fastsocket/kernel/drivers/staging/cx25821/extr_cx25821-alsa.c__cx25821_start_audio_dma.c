#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sram_channel {int dummy; } ;
struct cx25821_dev {int pci_irqmask; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct cx25821_buffer {int bpl; TYPE_1__ risc; } ;
struct TYPE_5__ {struct cx25821_dev* dev; int /*<<< orphan*/  count; struct cx25821_buffer* buf; } ;
typedef  TYPE_2__ snd_cx25821_card_t ;

/* Variables and functions */
 size_t AUDIO_SRAM_CHANNEL ; 
 int /*<<< orphan*/  AUD_A_CFG ; 
 int /*<<< orphan*/  AUD_A_GPCNT_CTL ; 
 int /*<<< orphan*/  AUD_A_INT_MSK ; 
 int /*<<< orphan*/  AUD_A_INT_STAT ; 
 int /*<<< orphan*/  AUD_A_LNGTH ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int FLD_AUD_CLK_ENABLE ; 
 int FLD_AUD_DST_A_FIFO_EN ; 
 int FLD_AUD_DST_A_RISC_EN ; 
 int FLD_AUD_DST_ENABLE ; 
 int FLD_AUD_DST_OF ; 
 int FLD_AUD_DST_OPC_ERR ; 
 int FLD_AUD_DST_PK_MODE ; 
 int FLD_AUD_DST_RISCI1 ; 
 int FLD_AUD_DST_SYNC ; 
 int GP_COUNT_CONTROL_RESET ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int PCI_MSK_AUD_INT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25821_set_gpiopin_direction (struct cx25821_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25821_sram_channel_setup_audio (struct cx25821_dev*,struct sram_channel*,int,int /*<<< orphan*/ ) ; 
 struct sram_channel* cx25821_sram_channels ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int _cx25821_start_audio_dma(snd_cx25821_card_t * chip)
{
	struct cx25821_buffer *buf = chip->buf;
	struct cx25821_dev *dev = chip->dev;
	struct sram_channel *audio_ch =
	    &cx25821_sram_channels[AUDIO_SRAM_CHANNEL];
	u32 tmp = 0;

	// enable output on the GPIO 0 for the MCLK ADC (Audio)
	cx25821_set_gpiopin_direction(chip->dev, 0, 0);

	/* Make sure RISC/FIFO are off before changing FIFO/RISC settings */
	cx_clear(AUD_INT_DMA_CTL,
		 FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN);

	/* setup fifo + format - out channel */
	cx25821_sram_channel_setup_audio(chip->dev, audio_ch, buf->bpl,
					 buf->risc.dma);

	/* sets bpl size */
	cx_write(AUD_A_LNGTH, buf->bpl);

	/* reset counter */
	cx_write(AUD_A_GPCNT_CTL, GP_COUNT_CONTROL_RESET);	//GP_COUNT_CONTROL_RESET = 0x3
	atomic_set(&chip->count, 0);

	//Set the input mode to 16-bit
	tmp = cx_read(AUD_A_CFG);
	cx_write(AUD_A_CFG,
		 tmp | FLD_AUD_DST_PK_MODE | FLD_AUD_DST_ENABLE |
		 FLD_AUD_CLK_ENABLE);

	//printk(KERN_INFO "DEBUG: Start audio DMA, %d B/line, cmds_start(0x%x)= %d lines/FIFO, %d periods, %d "
	//      "byte buffer\n", buf->bpl, audio_ch->cmds_start, cx_read(audio_ch->cmds_start + 12)>>1,
	//      chip->num_periods, buf->bpl * chip->num_periods);

	/* Enables corresponding bits at AUD_INT_STAT */
	cx_write(AUD_A_INT_MSK,
		 FLD_AUD_DST_RISCI1 | FLD_AUD_DST_OF | FLD_AUD_DST_SYNC |
		 FLD_AUD_DST_OPC_ERR);

	/* Clean any pending interrupt bits already set */
	cx_write(AUD_A_INT_STAT, ~0);

	/* enable audio irqs */
	cx_set(PCI_INT_MSK, chip->dev->pci_irqmask | PCI_MSK_AUD_INT);

	// Turn on audio downstream fifo and risc enable 0x101
	tmp = cx_read(AUD_INT_DMA_CTL);
	cx_set(AUD_INT_DMA_CTL,
	       tmp | (FLD_AUD_DST_A_RISC_EN | FLD_AUD_DST_A_FIFO_EN));

	mdelay(100);
	return 0;
}