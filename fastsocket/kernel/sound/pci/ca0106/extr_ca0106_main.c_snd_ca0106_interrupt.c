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
struct snd_ca0106_channel {TYPE_1__* epcm; scalar_t__ use; } ;
struct TYPE_5__ {unsigned int ipr_tx; unsigned int ipr_rx; int tx_enable; int rx_enable; int /*<<< orphan*/  (* interrupt_disable ) (TYPE_2__*,int) ;int /*<<< orphan*/  (* interrupt ) (TYPE_2__*,unsigned int) ;scalar_t__ dev_id; } ;
struct snd_ca0106 {scalar_t__ port; TYPE_2__ midi; struct snd_ca0106_channel* capture_channels; struct snd_ca0106_channel* playback_channels; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENDED_INT ; 
 scalar_t__ IPR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 unsigned int snd_ca0106_ptr_read (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static irqreturn_t snd_ca0106_interrupt(int irq, void *dev_id)
{
	unsigned int status;

	struct snd_ca0106 *chip = dev_id;
	int i;
	int mask;
        unsigned int stat76;
	struct snd_ca0106_channel *pchannel;

	status = inl(chip->port + IPR);
	if (! status)
		return IRQ_NONE;

        stat76 = snd_ca0106_ptr_read(chip, EXTENDED_INT, 0);
	/*
	snd_printk(KERN_DEBUG "interrupt status = 0x%08x, stat76=0x%08x\n",
		   status, stat76);
	snd_printk(KERN_DEBUG "ptr=0x%08x\n",
		   snd_ca0106_ptr_read(chip, PLAYBACK_POINTER, 0));
	*/
        mask = 0x11; /* 0x1 for one half, 0x10 for the other half period. */
	for(i = 0; i < 4; i++) {
		pchannel = &(chip->playback_channels[i]);
		if (stat76 & mask) {
/* FIXME: Select the correct substream for period elapsed */
			if(pchannel->use) {
				snd_pcm_period_elapsed(pchannel->epcm->substream);
				//printk(KERN_INFO "interrupt [%d] used\n", i);
                        }
		}
	        //printk(KERN_INFO "channel=%p\n",pchannel);
	        //printk(KERN_INFO "interrupt stat76[%d] = %08x, use=%d, channel=%d\n", i, stat76, pchannel->use, pchannel->number);
		mask <<= 1;
	}
        mask = 0x110000; /* 0x1 for one half, 0x10 for the other half period. */
	for(i = 0; i < 4; i++) {
		pchannel = &(chip->capture_channels[i]);
		if (stat76 & mask) {
/* FIXME: Select the correct substream for period elapsed */
			if(pchannel->use) {
				snd_pcm_period_elapsed(pchannel->epcm->substream);
				//printk(KERN_INFO "interrupt [%d] used\n", i);
                        }
		}
	        //printk(KERN_INFO "channel=%p\n",pchannel);
	        //printk(KERN_INFO "interrupt stat76[%d] = %08x, use=%d, channel=%d\n", i, stat76, pchannel->use, pchannel->number);
		mask <<= 1;
	}

        snd_ca0106_ptr_write(chip, EXTENDED_INT, 0, stat76);

	if (chip->midi.dev_id &&
	    (status & (chip->midi.ipr_tx|chip->midi.ipr_rx))) {
		if (chip->midi.interrupt)
			chip->midi.interrupt(&chip->midi, status);
		else
			chip->midi.interrupt_disable(&chip->midi, chip->midi.tx_enable | chip->midi.rx_enable);
	}

	// acknowledge the interrupt if necessary
	outl(status, chip->port+IPR);

	return IRQ_HANDLED;
}