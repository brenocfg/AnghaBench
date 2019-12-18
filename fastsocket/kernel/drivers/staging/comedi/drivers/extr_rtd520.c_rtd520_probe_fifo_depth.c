#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AREF_GROUND ; 
 unsigned int CR_PACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EIO ; 
 unsigned int FS_ADC_HEMPTY ; 
 int /*<<< orphan*/  RtdAdcClearFifo (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdAdcConversionSource (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdAdcStart (struct comedi_device*) ; 
 unsigned int RtdFifoStatus (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rtd_load_channelgain_list (struct comedi_device*,int,unsigned int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtd520_probe_fifo_depth(struct comedi_device *dev)
{
	unsigned int chanspec = CR_PACK(0, 0, AREF_GROUND);
	unsigned i;
	static const unsigned limit = 0x2000;
	unsigned fifo_size = 0;

	RtdAdcClearFifo(dev);
	rtd_load_channelgain_list(dev, 1, &chanspec);
	RtdAdcConversionSource(dev, 0);	/* software */
	/* convert  samples */
	for (i = 0; i < limit; ++i) {
		unsigned fifo_status;
		/* trigger conversion */
		RtdAdcStart(dev);
		udelay(1);
		fifo_status = RtdFifoStatus(dev);
		if ((fifo_status & FS_ADC_HEMPTY) == 0) {
			fifo_size = 2 * i;
			break;
		}
	}
	if (i == limit) {
		printk("\ncomedi: %s: failed to probe fifo size.\n", DRV_NAME);
		return -EIO;
	}
	RtdAdcClearFifo(dev);
	if (fifo_size != 0x400 && fifo_size != 0x2000) {
		printk
		    ("\ncomedi: %s: unexpected fifo size of %i, expected 1024 or 8192.\n",
		     DRV_NAME, fifo_size);
		return -EIO;
	}
	return fifo_size;
}