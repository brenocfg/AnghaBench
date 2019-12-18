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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {unsigned int events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {unsigned int ao_scan_count; int daccon; int /*<<< orphan*/  ao_continuous; } ;

/* Variables and functions */
 unsigned int COMEDI_CB_BLOCK ; 
 unsigned int COMEDI_CB_EOA ; 
 unsigned int COMEDI_CB_EOS ; 
 unsigned int COMEDI_CB_ERROR ; 
 unsigned int COMEDI_CB_OVERFLOW ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int PCI230P2_DAC_FIFOROOM_EMPTY ; 
 unsigned int PCI230P2_DAC_FIFOROOM_FULL ; 
 unsigned int PCI230P2_DAC_FIFOROOM_HALFTOFULL ; 
 unsigned int PCI230P2_DAC_FIFOROOM_ONETOHALF ; 
 unsigned short PCI230P2_DAC_FIFO_EMPTY ; 
 unsigned short PCI230P2_DAC_FIFO_FULL ; 
 unsigned short PCI230P2_DAC_FIFO_HALF ; 
 unsigned short PCI230P2_DAC_FIFO_UNDERRUN_LATCHED ; 
 int PCI230P2_DAC_INT_FIFO_EMPTY ; 
 int PCI230P2_DAC_INT_FIFO_MASK ; 
 scalar_t__ PCI230_DACCON ; 
 int /*<<< orphan*/  comedi_buf_get (struct comedi_async*,short*) ; 
 unsigned int comedi_buf_read_n_available (struct comedi_async*) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_stop (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci230_ao_write_fifo (struct comedi_device*,short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci230_handle_ao_fifo(struct comedi_device *dev,
				 struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int num_scans;
	unsigned int room;
	unsigned short dacstat;
	unsigned int i, n;
	unsigned int bytes_per_scan;
	unsigned int events = 0;
	int running;

	/* Get DAC FIFO status. */
	dacstat = inw(dev->iobase + PCI230_DACCON);

	/* Determine number of scans available in buffer. */
	bytes_per_scan = cmd->chanlist_len * sizeof(short);
	num_scans = comedi_buf_read_n_available(async) / bytes_per_scan;
	if (!devpriv->ao_continuous) {
		/* Fixed number of scans. */
		if (num_scans > devpriv->ao_scan_count) {
			num_scans = devpriv->ao_scan_count;
		}
		if (devpriv->ao_scan_count == 0) {
			/* End of acquisition. */
			events |= COMEDI_CB_EOA;
		}
	}
	if (events == 0) {
		/* Check for FIFO underrun. */
		if ((dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) != 0) {
			comedi_error(dev, "AO FIFO underrun");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
		/* Check for buffer underrun if FIFO less than half full
		 * (otherwise there will be loads of "DAC FIFO not half full"
		 * interrupts). */
		if ((num_scans == 0)
		    && ((dacstat & PCI230P2_DAC_FIFO_HALF) == 0)) {
			comedi_error(dev, "AO buffer underrun");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
	}
	if (events == 0) {
		/* Determine how much room is in the FIFO (in samples). */
		if ((dacstat & PCI230P2_DAC_FIFO_FULL) != 0) {
			room = PCI230P2_DAC_FIFOROOM_FULL;
		} else if ((dacstat & PCI230P2_DAC_FIFO_HALF) != 0) {
			room = PCI230P2_DAC_FIFOROOM_HALFTOFULL;
		} else if ((dacstat & PCI230P2_DAC_FIFO_EMPTY) != 0) {
			room = PCI230P2_DAC_FIFOROOM_EMPTY;
		} else {
			room = PCI230P2_DAC_FIFOROOM_ONETOHALF;
		}
		/* Convert room to number of scans that can be added. */
		room /= cmd->chanlist_len;
		/* Determine number of scans to process. */
		if (num_scans > room) {
			num_scans = room;
		}
		/* Process scans. */
		for (n = 0; n < num_scans; n++) {
			for (i = 0; i < cmd->chanlist_len; i++) {
				short datum;

				comedi_buf_get(async, &datum);
				pci230_ao_write_fifo(dev, datum,
						     CR_CHAN(cmd->chanlist[i]));
			}
		}
		events |= COMEDI_CB_EOS | COMEDI_CB_BLOCK;
		if (!devpriv->ao_continuous) {
			devpriv->ao_scan_count -= num_scans;
			if (devpriv->ao_scan_count == 0) {
				/* All data for the command has been written
				 * to FIFO.  Set FIFO interrupt trigger level
				 * to 'empty'. */
				devpriv->daccon = (devpriv->daccon
						   &
						   ~PCI230P2_DAC_INT_FIFO_MASK)
				    | PCI230P2_DAC_INT_FIFO_EMPTY;
				outw(devpriv->daccon,
				     dev->iobase + PCI230_DACCON);
			}
		}
		/* Check if FIFO underrun occurred while writing to FIFO. */
		dacstat = inw(dev->iobase + PCI230_DACCON);
		if ((dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) != 0) {
			comedi_error(dev, "AO FIFO underrun");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
	}
	if ((events & (COMEDI_CB_EOA | COMEDI_CB_ERROR | COMEDI_CB_OVERFLOW))
	    != 0) {
		/* Stopping AO due to completion or error. */
		pci230_ao_stop(dev, s);
		running = 0;
	} else {
		running = 1;
	}
	async->events |= events;
	return running;
}