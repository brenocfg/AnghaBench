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
typedef  int /*<<< orphan*/  u16 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  intCount; scalar_t__ aiCount; } ;

/* Variables and functions */
 int DMA0_ACTIVE ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ICS_DMA0_E ; 
 int /*<<< orphan*/  RtdAdcConversionSource (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdInterruptMask (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int RtdInterruptOverrunStatus (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdInterruptStatus (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPacerStop (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPacerStopSource (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int RtdPlxInterruptRead (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPlxInterruptWrite (struct comedi_device*,int) ; 
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int rtd_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	u16 status;

	RtdPacerStopSource(dev, 0);	/* stop on SOFTWARE stop */
	RtdPacerStop(dev);	/* Stop PACER */
	RtdAdcConversionSource(dev, 0);	/* software trigger only */
	RtdInterruptMask(dev, 0);
	devpriv->aiCount = 0;	/* stop and don't transfer any more */
#ifdef USE_DMA
	if (devpriv->flags & DMA0_ACTIVE) {
		RtdPlxInterruptWrite(dev,	/* disable any more interrupts */
				     RtdPlxInterruptRead(dev) & ~ICS_DMA0_E);
		abort_dma(dev, 0);
		devpriv->flags &= ~DMA0_ACTIVE;
	}
#endif /* USE_DMA */
	status = RtdInterruptStatus(dev);
	DPRINTK
	    ("rtd520: Acquisition canceled. %ld ints, intStat=%x, overStat=%x\n",
	     devpriv->intCount, status,
	     0xffff & RtdInterruptOverrunStatus(dev));
	return 0;
}