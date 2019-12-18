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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int ai_act_scan; unsigned int ai_n_scanlen; } ;
struct TYPE_3__ {unsigned int cur_chan; } ;

/* Variables and functions */
 unsigned int cfc_write_array_to_buffer (struct comedi_subdevice*,short*,unsigned int) ; 
 unsigned int defragment_dma_buffer (struct comedi_device*,struct comedi_subdevice*,short*,unsigned int) ; 
 TYPE_2__* devpriv ; 

__attribute__((used)) static unsigned int move_block_from_dma(struct comedi_device *dev,
					struct comedi_subdevice *s,
					short *dma_buffer,
					unsigned int num_samples)
{
	unsigned int num_bytes;

	num_samples = defragment_dma_buffer(dev, s, dma_buffer, num_samples);
	devpriv->ai_act_scan +=
	    (s->async->cur_chan + num_samples) / devpriv->ai_n_scanlen;
	s->async->cur_chan += num_samples;
	s->async->cur_chan %= devpriv->ai_n_scanlen;
	num_bytes =
	    cfc_write_array_to_buffer(s, dma_buffer,
				      num_samples * sizeof(short));
	if (num_bytes < num_samples * sizeof(short))
		return -1;
	return 0;
}