#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_7__ {int input; int rate; } ;
struct saa7134_dev {TYPE_2__ dmasound; TYPE_1__* pci; } ;
struct TYPE_9__ {int capture_source_addr; int* capture_source; TYPE_3__** capture_ctl; int /*<<< orphan*/  card; int /*<<< orphan*/  mixer_lock; struct saa7134_dev* dev; } ;
typedef  TYPE_4__ snd_card_saa7134_t ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int device; } ;

/* Variables and functions */
#define  MIXER_ADDR_LINE1 133 
#define  MIXER_ADDR_LINE2 132 
#define  MIXER_ADDR_TVTUNER 131 
 int MIXER_ADDR_UNSELECTED ; 
#define  PCI_DEVICE_ID_PHILIPS_SAA7133 130 
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 129 
#define  PCI_DEVICE_ID_PHILIPS_SAA7135 128 
 int /*<<< orphan*/  SAA7133_ANALOG_IO_SELECT ; 
 int /*<<< orphan*/  SAA7133_DIGITAL_INPUT_XBAR1 ; 
 int /*<<< orphan*/  SAA7133_DIGITAL_OUTPUT_SEL1 ; 
 int /*<<< orphan*/  SAA7134_ANALOG_IO_SELECT ; 
 int /*<<< orphan*/  SAA7134_AUDIO_FORMAT_CTRL ; 
 int /*<<< orphan*/  SAA7134_SIF_SAMPLE_FREQ ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa_dsp_writel (struct saa7134_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_saa7134_capsrc_set(struct snd_kcontrol *kcontrol,
				  int left, int right, bool force_notify)
{
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	int change = 0, addr = kcontrol->private_value;
	int active, old_addr;
	u32 anabar, xbarin;
	int analog_io, rate;
	struct saa7134_dev *dev;

	dev = chip->dev;

	spin_lock_irq(&chip->mixer_lock);

	active = left != 0 || right != 0;
	old_addr = chip->capture_source_addr;

	/* The active capture source cannot be deactivated */
	if (active) {
		change = old_addr != addr ||
			 chip->capture_source[0] != left ||
			 chip->capture_source[1] != right;

		chip->capture_source[0] = left;
		chip->capture_source[1] = right;
		chip->capture_source_addr = addr;
		dev->dmasound.input = addr;
	}
	spin_unlock_irq(&chip->mixer_lock);

	if (change) {
		switch (dev->pci->device) {

		case PCI_DEVICE_ID_PHILIPS_SAA7134:
			switch (addr) {
			case MIXER_ADDR_TVTUNER:
				saa_andorb(SAA7134_AUDIO_FORMAT_CTRL,
					   0xc0, 0xc0);
				saa_andorb(SAA7134_SIF_SAMPLE_FREQ,
					   0x03, 0x00);
				break;
			case MIXER_ADDR_LINE1:
			case MIXER_ADDR_LINE2:
				analog_io = (MIXER_ADDR_LINE1 == addr) ?
					     0x00 : 0x08;
				rate = (32000 == dev->dmasound.rate) ?
					0x01 : 0x03;
				saa_andorb(SAA7134_ANALOG_IO_SELECT,
					   0x08, analog_io);
				saa_andorb(SAA7134_AUDIO_FORMAT_CTRL,
					   0xc0, 0x80);
				saa_andorb(SAA7134_SIF_SAMPLE_FREQ,
					   0x03, rate);
				break;
			}

			break;
		case PCI_DEVICE_ID_PHILIPS_SAA7133:
		case PCI_DEVICE_ID_PHILIPS_SAA7135:
			xbarin = 0x03; /* adc */
			anabar = 0;
			switch (addr) {
			case MIXER_ADDR_TVTUNER:
				xbarin = 0; /* Demodulator */
				anabar = 2; /* DACs */
				break;
			case MIXER_ADDR_LINE1:
				anabar = 0;  /* aux1, aux1 */
				break;
			case MIXER_ADDR_LINE2:
				anabar = 9;  /* aux2, aux2 */
				break;
			}

			/* output xbar always main channel */
			saa_dsp_writel(dev, SAA7133_DIGITAL_OUTPUT_SEL1,
				       0xbbbb10);

			if (left || right) {
				/* We've got data, turn the input on */
				saa_dsp_writel(dev, SAA7133_DIGITAL_INPUT_XBAR1,
					       xbarin);
				saa_writel(SAA7133_ANALOG_IO_SELECT, anabar);
			} else {
				saa_dsp_writel(dev, SAA7133_DIGITAL_INPUT_XBAR1,
					       0);
				saa_writel(SAA7133_ANALOG_IO_SELECT, 0);
			}
			break;
		}
	}

	if (change) {
		if (force_notify)
			snd_ctl_notify(chip->card,
				       SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->capture_ctl[addr]->id);

		if (old_addr != MIXER_ADDR_UNSELECTED && old_addr != addr)
			snd_ctl_notify(chip->card,
				       SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->capture_ctl[old_addr]->id);
	}

	return change;
}