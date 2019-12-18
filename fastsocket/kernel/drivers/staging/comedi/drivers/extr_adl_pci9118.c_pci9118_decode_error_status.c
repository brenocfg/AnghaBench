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
struct TYPE_4__ {int ai_maskerr; unsigned char ai_maskharderr; } ;
struct TYPE_3__ {int events; } ;

/* Variables and functions */
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  pci9118_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static char pci9118_decode_error_status(struct comedi_device *dev,
					struct comedi_subdevice *s,
					unsigned char m)
{
	if (m & 0x100) {
		comedi_error(dev, "A/D FIFO Full status (Fatal Error!)");
		devpriv->ai_maskerr &= ~0x100L;
	}
	if (m & 0x008) {
		comedi_error(dev,
			     "A/D Burst Mode Overrun Status (Fatal Error!)");
		devpriv->ai_maskerr &= ~0x008L;
	}
	if (m & 0x004) {
		comedi_error(dev, "A/D Over Speed Status (Warning!)");
		devpriv->ai_maskerr &= ~0x004L;
	}
	if (m & 0x002) {
		comedi_error(dev, "A/D Overrun Status (Fatal Error!)");
		devpriv->ai_maskerr &= ~0x002L;
	}
	if (m & devpriv->ai_maskharderr) {
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		pci9118_ai_cancel(dev, s);
		comedi_event(dev, s);
		return 1;
	}

	return 0;
}