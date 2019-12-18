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
struct comedi_insn {int chanspec; int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ adc_fifo; scalar_t__ control_status; } ;

/* Variables and functions */
 scalar_t__ ADCDATA ; 
 scalar_t__ ADCFIFOCLR ; 
 scalar_t__ ADCMUX_CONT ; 
 scalar_t__ AREF_DIFF ; 
 unsigned int BEGIN_SCAN (int) ; 
 scalar_t__ CALIBRATION_REG ; 
 int CR_ALT_SOURCE ; 
 scalar_t__ CR_AREF (int) ; 
 int CR_CHAN (int) ; 
 int CR_RANGE (int) ; 
 unsigned int END_SCAN (int) ; 
 int EOC ; 
 int ETIMEDOUT ; 
 unsigned int GAIN_BITS (int) ; 
 int IS_UNIPOLAR ; 
 unsigned int SE ; 
 unsigned int UNIP ; 
 unsigned int cal_enable_bits (struct comedi_device*) ; 
 TYPE_1__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static int cb_pcidas_ai_rinsn(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	int n, i;
	unsigned int bits;
	static const int timeout = 10000;
	int channel;
	/*  enable calibration input if appropriate */
	if (insn->chanspec & CR_ALT_SOURCE) {
		outw(cal_enable_bits(dev),
		     devpriv->control_status + CALIBRATION_REG);
		channel = 0;
	} else {
		outw(0, devpriv->control_status + CALIBRATION_REG);
		channel = CR_CHAN(insn->chanspec);
	}
	/*  set mux limits and gain */
	bits = BEGIN_SCAN(channel) |
	    END_SCAN(channel) | GAIN_BITS(CR_RANGE(insn->chanspec));
	/*  set unipolar/bipolar */
	if (CR_RANGE(insn->chanspec) & IS_UNIPOLAR)
		bits |= UNIP;
	/*  set singleended/differential */
	if (CR_AREF(insn->chanspec) != AREF_DIFF)
		bits |= SE;
	outw(bits, devpriv->control_status + ADCMUX_CONT);

	/* clear fifo */
	outw(0, devpriv->adc_fifo + ADCFIFOCLR);

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outw(0, devpriv->adc_fifo + ADCDATA);

		/* wait for conversion to end */
		/* return -ETIMEDOUT if there is a timeout */
		for (i = 0; i < timeout; i++) {
			if (inw(devpriv->control_status + ADCMUX_CONT) & EOC)
				break;
		}
		if (i == timeout)
			return -ETIMEDOUT;

		/* read data */
		data[n] = inw(devpriv->adc_fifo + ADCDATA);
	}

	/* return the number of samples read/written */
	return n;
}