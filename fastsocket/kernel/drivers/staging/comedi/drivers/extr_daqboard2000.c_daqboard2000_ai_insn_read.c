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
struct daqboard2000_hw {int acqControl; int acqPacerClockDivLow; unsigned int acqResultsFIFO; scalar_t__ acqPacerClockDivHigh; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {struct daqboard2000_hw* daq; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int DAQBOARD2000_AcqConfigPipeFull ; 
 int DAQBOARD2000_AcqLogicScanning ; 
 int DAQBOARD2000_AcqResetConfigPipe ; 
 int DAQBOARD2000_AcqResetResultsFifo ; 
 int DAQBOARD2000_AcqResetScanListFifo ; 
 int DAQBOARD2000_AcqResultsFIFOHasValidData ; 
 int DAQBOARD2000_AdcPacerDisable ; 
 int DAQBOARD2000_AdcPacerEnable ; 
 int DAQBOARD2000_SeqStartScanList ; 
 int DAQBOARD2000_SeqStopScanList ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  setup_sampling (struct comedi_device*,int,int) ; 

__attribute__((used)) static int daqboard2000_ai_insn_read(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	int i;
	struct daqboard2000_hw *fpga = devpriv->daq;
	int gain, chan, timeout;

	fpga->acqControl =
	    DAQBOARD2000_AcqResetScanListFifo |
	    DAQBOARD2000_AcqResetResultsFifo | DAQBOARD2000_AcqResetConfigPipe;

	/* If pacer clock is not set to some high value (> 10 us), we
	   risk multiple samples to be put into the result FIFO. */
	fpga->acqPacerClockDivLow = 1000000;	/* 1 second, should be long enough */
	fpga->acqPacerClockDivHigh = 0;

	gain = CR_RANGE(insn->chanspec);
	chan = CR_CHAN(insn->chanspec);

	/* This doesn't look efficient.  I decided to take the conservative
	 * approach when I did the insn conversion.  Perhaps it would be
	 * better to have broken it completely, then someone would have been
	 * forced to fix it.  --ds */
	for (i = 0; i < insn->n; i++) {
		setup_sampling(dev, chan, gain);
		/* Enable reading from the scanlist FIFO */
		fpga->acqControl = DAQBOARD2000_SeqStartScanList;
		for (timeout = 0; timeout < 20; timeout++) {
			if (fpga->acqControl & DAQBOARD2000_AcqConfigPipeFull) {
				break;
			}
			/* udelay(2); */
		}
		fpga->acqControl = DAQBOARD2000_AdcPacerEnable;
		for (timeout = 0; timeout < 20; timeout++) {
			if (fpga->acqControl & DAQBOARD2000_AcqLogicScanning) {
				break;
			}
			/* udelay(2); */
		}
		for (timeout = 0; timeout < 20; timeout++) {
			if (fpga->acqControl &
			    DAQBOARD2000_AcqResultsFIFOHasValidData) {
				break;
			}
			/* udelay(2); */
		}
		data[i] = fpga->acqResultsFIFO;
		fpga->acqControl = DAQBOARD2000_AdcPacerDisable;
		fpga->acqControl = DAQBOARD2000_SeqStopScanList;
	}

	return i;
}