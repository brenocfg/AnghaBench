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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
typedef  int s16 ;
struct TYPE_2__ {int /*<<< orphan*/  chanBipolar; } ;

/* Variables and functions */
 scalar_t__ CHAN_ARRAY_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
 int ETIMEDOUT ; 
 int FS_ADC_NOT_EMPTY ; 
 int RTD_ADC_TIMEOUT ; 
 int /*<<< orphan*/  RtdAdcClearFifo (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdAdcConversionSource (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int RtdAdcFifoGet (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdAdcStart (struct comedi_device*) ; 
 int RtdFifoStatus (struct comedi_device*) ; 
 int /*<<< orphan*/  WAIT_QUIETLY ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  rtd_load_channelgain_list (struct comedi_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtd_ai_rinsn(struct comedi_device *dev,
			struct comedi_subdevice *s, struct comedi_insn *insn,
			unsigned int *data)
{
	int n, ii;
	int stat;

	/* clear any old fifo data */
	RtdAdcClearFifo(dev);

	/* write channel to multiplexer and clear channel gain table */
	rtd_load_channelgain_list(dev, 1, &insn->chanspec);

	/* set conversion source */
	RtdAdcConversionSource(dev, 0);	/* software */

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		s16 d;
		/* trigger conversion */
		RtdAdcStart(dev);

		for (ii = 0; ii < RTD_ADC_TIMEOUT; ++ii) {
			stat = RtdFifoStatus(dev);
			if (stat & FS_ADC_NOT_EMPTY)	/* 1 -> not empty */
				break;
			WAIT_QUIETLY;
		}
		if (ii >= RTD_ADC_TIMEOUT) {
			DPRINTK
			    ("rtd520: Error: ADC never finished! FifoStatus=0x%x\n",
			     stat ^ 0x6666);
			return -ETIMEDOUT;
		}

		/* read data */
		d = RtdAdcFifoGet(dev);	/* get 2s comp value */
		/*printk ("rtd520: Got 0x%x after %d usec\n", d, ii+1); */
		d = d >> 3;	/* low 3 bits are marker lines */
		if (CHAN_ARRAY_TEST(devpriv->chanBipolar, 0)) {
			data[n] = d + 2048;	/* convert to comedi unsigned data */
		} else {
			data[n] = d;
		}
	}

	/* return the number of samples read/written */
	return n;
}