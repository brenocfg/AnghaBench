#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_maxsize; TYPE_2__* dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT2821_STRIG ; 
 int EINVAL ; 
 int EPIPE ; 
 int cfc_read_array_from_buffer (struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  prep_ao_dma (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  update_supcsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt282x_ao_inttrig(struct comedi_device *dev,
			     struct comedi_subdevice *s, unsigned int x)
{
	int size;

	if (x != 0)
		return -EINVAL;

	size = cfc_read_array_from_buffer(s, devpriv->dma[0].buf,
					  devpriv->dma_maxsize);
	if (size == 0) {
		printk("dt282x: AO underrun\n");
		return -EPIPE;
	}
	prep_ao_dma(dev, 0, size);

	size = cfc_read_array_from_buffer(s, devpriv->dma[1].buf,
					  devpriv->dma_maxsize);
	if (size == 0) {
		printk("dt282x: AO underrun\n");
		return -EPIPE;
	}
	prep_ao_dma(dev, 1, size);

	update_supcsr(DT2821_STRIG);
	s->async->inttrig = NULL;

	return 1;
}