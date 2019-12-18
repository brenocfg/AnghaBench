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
struct saa7134_dev {size_t board; TYPE_1__* pci; } ;
struct TYPE_4__ {int audio_clock; } ;
struct TYPE_3__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_PHILIPS_SAA7133 130 
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 129 
#define  PCI_DEVICE_ID_PHILIPS_SAA7135 128 
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCK0 ; 
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCK1 ; 
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCK2 ; 
 int /*<<< orphan*/  SAA7134_AUDIO_PLL_CTRL ; 
 int /*<<< orphan*/  SAA7134_NICAM_ERROR_HIGH ; 
 int /*<<< orphan*/  SAA7134_NICAM_ERROR_LOW ; 
 int UNSET ; 
 int audio_clock_override ; 
 int /*<<< orphan*/  need_resched () ; 
 TYPE_2__* saa7134_boards ; 
 int /*<<< orphan*/  saa_dsp_writel (struct saa7134_dev*,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int,int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  udelay (int) ; 

void saa7134_tvaudio_init(struct saa7134_dev *dev)
{
	int clock = saa7134_boards[dev->board].audio_clock;

	if (UNSET != audio_clock_override)
		clock = audio_clock_override;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		/* init all audio registers */
		saa_writeb(SAA7134_AUDIO_PLL_CTRL,   0x00);
		if (need_resched())
			schedule();
		else
			udelay(10);

		saa_writeb(SAA7134_AUDIO_CLOCK0,      clock        & 0xff);
		saa_writeb(SAA7134_AUDIO_CLOCK1,     (clock >>  8) & 0xff);
		saa_writeb(SAA7134_AUDIO_CLOCK2,     (clock >> 16) & 0xff);
		/* frame locked audio is mandatory for NICAM */
		saa_writeb(SAA7134_AUDIO_PLL_CTRL,   0x01);
		saa_writeb(SAA7134_NICAM_ERROR_LOW,  0x14);
		saa_writeb(SAA7134_NICAM_ERROR_HIGH, 0x50);
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		saa_writel(0x598 >> 2, clock);
		saa_dsp_writel(dev, 0x474 >> 2, 0x00);
		saa_dsp_writel(dev, 0x450 >> 2, 0x00);
	}
}