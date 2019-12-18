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
struct comedi_device {int /*<<< orphan*/  irq; } ;
struct comedi_cmd {int chanlist_len; int scan_begin_src; int flags; int scan_begin_arg; int stop_src; int stop_arg; int convert_src; int convert_arg; int /*<<< orphan*/  chanlist; } ;
struct TYPE_6__ {int flags; int fifoLen; int transCount; int aiCount; int /*<<< orphan*/  intMask; TYPE_2__* dma0Chain; scalar_t__ dma0Offset; scalar_t__ intCount; } ;
struct TYPE_5__ {int /*<<< orphan*/  next; } ;
struct TYPE_4__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int DMA0_ACTIVE ; 
 int /*<<< orphan*/  DMAS_ADFIFO_HALF_FULL ; 
 int DMA_CHAIN_COUNT ; 
 int /*<<< orphan*/  DMA_MODE_BITS ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int ENXIO ; 
 int ICS_DMA0_A ; 
 int ICS_DMA0_E ; 
 int /*<<< orphan*/  IRQM_ADC_ABOUT_CNT ; 
 int PLX_CLEAR_DMA_INTR_BIT ; 
 int PLX_DMA_EN_BIT ; 
 int PLX_DMA_START_BIT ; 
 int /*<<< orphan*/  RtdAboutCounter (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdAboutStopEnable (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdAdcClearFifo (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdAdcConversionSource (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdBurstCounter (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdBurstStartSource (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdDma0Control (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdDma0Mode (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdDma0Next (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdDma0Reset (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdDma0Source (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdInterruptClear (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdInterruptClearMask (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdInterruptMask (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdInterruptOverrunClear (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPacerClockSource (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdPacerCounter (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdPacerStart (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPacerStartSource (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdPacerStop (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPacerStopSource (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int RtdPlxInterruptRead (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdPlxInterruptWrite (struct comedi_device*,int) ; 
 int SEND_EOS ; 
 int TRANS_TARGET_PERIOD ; 
#define  TRIG_COUNT 131 
#define  TRIG_EXT 130 
#define  TRIG_NONE 129 
 int /*<<< orphan*/  TRIG_ROUND_NEAREST ; 
#define  TRIG_TIMER 128 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  rtd_load_channelgain_list (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int rtd_ns_to_timer (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtd_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	int timer;

	/* stop anything currently running */
	RtdPacerStopSource(dev, 0);	/* stop on SOFTWARE stop */
	RtdPacerStop(dev);	/* make sure PACER is stopped */
	RtdAdcConversionSource(dev, 0);	/* software trigger only */
	RtdInterruptMask(dev, 0);
#ifdef USE_DMA
	if (devpriv->flags & DMA0_ACTIVE) {	/* cancel anything running */
		RtdPlxInterruptWrite(dev,	/* disable any more interrupts */
				     RtdPlxInterruptRead(dev) & ~ICS_DMA0_E);
		abort_dma(dev, 0);
		devpriv->flags &= ~DMA0_ACTIVE;
		if (RtdPlxInterruptRead(dev) & ICS_DMA0_A) {	/*clear pending int */
			RtdDma0Control(dev, PLX_CLEAR_DMA_INTR_BIT);
		}
	}
	RtdDma0Reset(dev);	/* reset onboard state */
#endif /* USE_DMA */
	RtdAdcClearFifo(dev);	/* clear any old data */
	RtdInterruptOverrunClear(dev);
	devpriv->intCount = 0;

	if (!dev->irq) {	/* we need interrupts for this */
		DPRINTK("rtd520: ERROR! No interrupt available!\n");
		return -ENXIO;
	}

	/* start configuration */
	/* load channel list and reset CGT */
	rtd_load_channelgain_list(dev, cmd->chanlist_len, cmd->chanlist);

	/* setup the common case and override if needed */
	if (cmd->chanlist_len > 1) {
		/*DPRINTK ("rtd520: Multi channel setup\n"); */
		RtdPacerStartSource(dev, 0);	/* software triggers pacer */
		RtdBurstStartSource(dev, 1);	/* PACER triggers burst */
		RtdAdcConversionSource(dev, 2);	/* BURST triggers ADC */
	} else {		/* single channel */
		/*DPRINTK ("rtd520: single channel setup\n"); */
		RtdPacerStartSource(dev, 0);	/* software triggers pacer */
		RtdAdcConversionSource(dev, 1);	/* PACER triggers ADC */
	}
	RtdAboutCounter(dev, devpriv->fifoLen / 2 - 1);	/* 1/2 FIFO */

	if (TRIG_TIMER == cmd->scan_begin_src) {
		/* scan_begin_arg is in nanoseconds */
		/* find out how many samples to wait before transferring */
		if (cmd->flags & TRIG_WAKE_EOS) {
			/* this may generate un-sustainable interrupt rates */
			/* the application is responsible for doing the right thing */
			devpriv->transCount = cmd->chanlist_len;
			devpriv->flags |= SEND_EOS;
		} else {
			/* arrange to transfer data periodically */
			devpriv->transCount
			    =
			    (TRANS_TARGET_PERIOD * cmd->chanlist_len) /
			    cmd->scan_begin_arg;
			if (devpriv->transCount < cmd->chanlist_len) {
				/* tranfer after each scan (and avoid 0) */
				devpriv->transCount = cmd->chanlist_len;
			} else {	/* make a multiple of scan length */
				devpriv->transCount =
				    (devpriv->transCount +
				     cmd->chanlist_len - 1)
				    / cmd->chanlist_len;
				devpriv->transCount *= cmd->chanlist_len;
			}
			devpriv->flags |= SEND_EOS;
		}
		if (devpriv->transCount >= (devpriv->fifoLen / 2)) {
			/* out of counter range, use 1/2 fifo instead */
			devpriv->transCount = 0;
			devpriv->flags &= ~SEND_EOS;
		} else {
			/* interrupt for each tranfer */
			RtdAboutCounter(dev, devpriv->transCount - 1);
		}

		DPRINTK
		    ("rtd520: scanLen=%d tranferCount=%d fifoLen=%d\n  scanTime(ns)=%d flags=0x%x\n",
		     cmd->chanlist_len, devpriv->transCount, devpriv->fifoLen,
		     cmd->scan_begin_arg, devpriv->flags);
	} else {		/* unknown timing, just use 1/2 FIFO */
		devpriv->transCount = 0;
		devpriv->flags &= ~SEND_EOS;
	}
	RtdPacerClockSource(dev, 1);	/* use INTERNAL 8Mhz clock source */
	RtdAboutStopEnable(dev, 1);	/* just interrupt, dont stop */

	/* BUG??? these look like enumerated values, but they are bit fields */

	/* First, setup when to stop */
	switch (cmd->stop_src) {
	case TRIG_COUNT:	/* stop after N scans */
		devpriv->aiCount = cmd->stop_arg * cmd->chanlist_len;
		if ((devpriv->transCount > 0)
		    && (devpriv->transCount > devpriv->aiCount)) {
			devpriv->transCount = devpriv->aiCount;
		}
		break;

	case TRIG_NONE:	/* stop when cancel is called */
		devpriv->aiCount = -1;	/* read forever */
		break;

	default:
		DPRINTK("rtd520: Warning! ignoring stop_src mode %d\n",
			cmd->stop_src);
	}

	/* Scan timing */
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:	/* periodic scanning */
		timer = rtd_ns_to_timer(&cmd->scan_begin_arg,
					TRIG_ROUND_NEAREST);
		/* set PACER clock */
		/*DPRINTK ("rtd520: loading %d into pacer\n", timer); */
		RtdPacerCounter(dev, timer);

		break;

	case TRIG_EXT:
		RtdPacerStartSource(dev, 1);	/* EXTERNALy trigger pacer */
		break;

	default:
		DPRINTK("rtd520: Warning! ignoring scan_begin_src mode %d\n",
			cmd->scan_begin_src);
	}

	/* Sample timing within a scan */
	switch (cmd->convert_src) {
	case TRIG_TIMER:	/* periodic */
		if (cmd->chanlist_len > 1) {	/* only needed for multi-channel */
			timer = rtd_ns_to_timer(&cmd->convert_arg,
						TRIG_ROUND_NEAREST);
			/* setup BURST clock */
			/*DPRINTK ("rtd520: loading %d into burst\n", timer); */
			RtdBurstCounter(dev, timer);
		}

		break;

	case TRIG_EXT:		/* external */
		RtdBurstStartSource(dev, 2);	/* EXTERNALy trigger burst */
		break;

	default:
		DPRINTK("rtd520: Warning! ignoring convert_src mode %d\n",
			cmd->convert_src);
	}
	/* end configuration */

	/* This doesn't seem to work.  There is no way to clear an interrupt
	   that the priority controller has queued! */
	RtdInterruptClearMask(dev, ~0);	/* clear any existing flags */
	RtdInterruptClear(dev);

	/* TODO: allow multiple interrupt sources */
	if (devpriv->transCount > 0) {	/* transfer every N samples */
		RtdInterruptMask(dev, IRQM_ADC_ABOUT_CNT);
		DPRINTK("rtd520: Transferring every %d\n", devpriv->transCount);
	} else {		/* 1/2 FIFO transfers */
#ifdef USE_DMA
		devpriv->flags |= DMA0_ACTIVE;

		/* point to first transfer in ring */
		devpriv->dma0Offset = 0;
		RtdDma0Mode(dev, DMA_MODE_BITS);
		RtdDma0Next(dev,	/* point to first block */
			    devpriv->dma0Chain[DMA_CHAIN_COUNT - 1].next);
		RtdDma0Source(dev, DMAS_ADFIFO_HALF_FULL);	/* set DMA trigger source */

		RtdPlxInterruptWrite(dev,	/* enable interrupt */
				     RtdPlxInterruptRead(dev) | ICS_DMA0_E);
		/* Must be 2 steps.  See PLX app note about "Starting a DMA transfer" */
		RtdDma0Control(dev, PLX_DMA_EN_BIT);	/* enable DMA (clear INTR?) */
		RtdDma0Control(dev, PLX_DMA_EN_BIT | PLX_DMA_START_BIT);	/*start DMA */
		DPRINTK("rtd520: Using DMA0 transfers. plxInt %x RtdInt %x\n",
			RtdPlxInterruptRead(dev), devpriv->intMask);
#else /* USE_DMA */
		RtdInterruptMask(dev, IRQM_ADC_ABOUT_CNT);
		DPRINTK("rtd520: Transferring every 1/2 FIFO\n");
#endif /* USE_DMA */
	}

	/* BUG: start_src is ASSUMED to be TRIG_NOW */
	/* BUG? it seems like things are running before the "start" */
	RtdPacerStart(dev);	/* Start PACER */
	return 0;
}