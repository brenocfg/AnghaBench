#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_12__ {TYPE_4__* asics; } ;
struct TYPE_8__ {int asic; int num_asic_chans; int asic_chan; scalar_t__ active; scalar_t__ enabled_mask; } ;
struct TYPE_9__ {TYPE_2__ intr; } ;
struct TYPE_11__ {TYPE_3__ dio; } ;
struct TYPE_10__ {scalar_t__ iobase; } ;
struct TYPE_7__ {scalar_t__ inttrig; } ;

/* Variables and functions */
 int CHANS_PER_PORT ; 
 int /*<<< orphan*/  PAGE_ENAB ; 
 scalar_t__ REG_ENAB0 ; 
 TYPE_6__* devpriv ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* subpriv ; 
 int /*<<< orphan*/  switch_page (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmmio_stop_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	int nports, firstport, asic, port;

	asic = subpriv->dio.intr.asic;
	if (asic < 0)
		return;		/* not an interrupt subdev */

	subpriv->dio.intr.enabled_mask = 0;
	subpriv->dio.intr.active = 0;
	s->async->inttrig = 0;
	nports = subpriv->dio.intr.num_asic_chans / CHANS_PER_PORT;
	firstport = subpriv->dio.intr.asic_chan / CHANS_PER_PORT;
	switch_page(dev, asic, PAGE_ENAB);
	for (port = firstport; port < firstport + nports; ++port) {
		/* disable all intrs for this subdev.. */
		outb(0, devpriv->asics[asic].iobase + REG_ENAB0 + port);
	}
}