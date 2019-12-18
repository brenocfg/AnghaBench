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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {unsigned int scan_end_arg; int flags; } ;
struct TYPE_4__ {unsigned int ai_scan_pos; unsigned int ai_scan_count; scalar_t__ hwver; unsigned int adcfifothresh; unsigned short adccon; scalar_t__ ai_continuous; } ;
struct TYPE_3__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ PCI230P_ADCFFTH ; 
 unsigned short PCI230P_ADC_INT_FIFO_THRESH ; 
 scalar_t__ PCI230_ADCCON ; 
 unsigned int PCI230_ADC_FIFOLEVEL_HALFFULL ; 
 unsigned short PCI230_ADC_INT_FIFO_HALF ; 
 unsigned short PCI230_ADC_INT_FIFO_MASK ; 
 unsigned short PCI230_ADC_INT_FIFO_NEMPTY ; 
 int TRIG_WAKE_EOS ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static void pci230_ai_update_fifo_trigger_level(struct comedi_device *dev,
						struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int scanlen = cmd->scan_end_arg;
	unsigned int wake;
	unsigned short triglev;
	unsigned short adccon;

	if ((cmd->flags & TRIG_WAKE_EOS) != 0) {
		/* Wake at end of scan. */
		wake = scanlen - devpriv->ai_scan_pos;
	} else {
		if (devpriv->ai_continuous
		    || (devpriv->ai_scan_count >= PCI230_ADC_FIFOLEVEL_HALFFULL)
		    || (scanlen >= PCI230_ADC_FIFOLEVEL_HALFFULL)) {
			wake = PCI230_ADC_FIFOLEVEL_HALFFULL;
		} else {
			wake = (devpriv->ai_scan_count * scanlen)
			    - devpriv->ai_scan_pos;
		}
	}
	if (wake >= PCI230_ADC_FIFOLEVEL_HALFFULL) {
		triglev = PCI230_ADC_INT_FIFO_HALF;
	} else {
		if ((wake > 1) && (devpriv->hwver > 0)) {
			/* PCI230+/260+ programmable FIFO interrupt level. */
			if (devpriv->adcfifothresh != wake) {
				devpriv->adcfifothresh = wake;
				outw(wake, dev->iobase + PCI230P_ADCFFTH);
			}
			triglev = PCI230P_ADC_INT_FIFO_THRESH;
		} else {
			triglev = PCI230_ADC_INT_FIFO_NEMPTY;
		}
	}
	adccon = (devpriv->adccon & ~PCI230_ADC_INT_FIFO_MASK) | triglev;
	if (adccon != devpriv->adccon) {
		devpriv->adccon = adccon;
		outw(adccon, dev->iobase + PCI230_ADCCON);
	}
}