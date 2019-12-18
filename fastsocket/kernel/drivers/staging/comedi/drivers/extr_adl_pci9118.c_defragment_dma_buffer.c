#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int ai_add_front; unsigned int ai_n_chan; unsigned int ai_add_back; unsigned int ai_act_dmapos; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 

__attribute__((used)) static unsigned int defragment_dma_buffer(struct comedi_device *dev,
					  struct comedi_subdevice *s,
					  short *dma_buffer,
					  unsigned int num_samples)
{
	unsigned int i = 0, j = 0;
	unsigned int start_pos = devpriv->ai_add_front,
	    stop_pos = devpriv->ai_add_front + devpriv->ai_n_chan;
	unsigned int raw_scanlen = devpriv->ai_add_front + devpriv->ai_n_chan +
	    devpriv->ai_add_back;

	for (i = 0; i < num_samples; i++) {
		if (devpriv->ai_act_dmapos >= start_pos &&
		    devpriv->ai_act_dmapos < stop_pos) {
			dma_buffer[j++] = dma_buffer[i];
		}
		devpriv->ai_act_dmapos++;
		devpriv->ai_act_dmapos %= raw_scanlen;
	}

	return j;
}