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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned long ulConvertionRate; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned char MPC624_ADBUSY ; 
 scalar_t__ MPC624_ADC ; 
 int MPC624_ADCS ; 
 int MPC624_ADSCK ; 
 int MPC624_ADSDI ; 
 int MPC624_ADSDO ; 
 unsigned long MPC624_DMY_BIT ; 
 unsigned long MPC624_EOC_BIT ; 
 scalar_t__ MPC624_GNMUXCH ; 
 unsigned long MPC624_SGN_BIT ; 
 int TIMEOUT ; 
 TYPE_1__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mpc624_ai_rinsn(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_insn *insn,
			   unsigned int *data)
{
	int n, i;
	unsigned long int data_in, data_out;
	unsigned char ucPort;

	/*  WARNING: We always write 0 to GNSWA bit, so the channel range is +-/10.1Vdc */
	outb(insn->chanspec, dev->iobase + MPC624_GNMUXCH);
/* printk("Channel %d: \n", insn->chanspec); */
	if (!insn->n) {
		printk("MPC624: Warning, no data to aquire\n");
		return 0;
	}

	for (n = 0; n < insn->n; n++) {
		/*  Trigger the convertion */
		outb(MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(MPC624_ADCS | MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udelay(1);
		outb(0, dev->iobase + MPC624_ADC);
		udelay(1);

		/*  Wait for the convertion to end */
		for (i = 0; i < TIMEOUT; i++) {
			ucPort = inb(dev->iobase + MPC624_ADC);
			if (ucPort & MPC624_ADBUSY)
				udelay(1000);
			else
				break;
		}
		if (i == TIMEOUT) {
			printk("MPC624: timeout (%dms)\n", TIMEOUT);
			data[n] = 0;
			return -ETIMEDOUT;
		}
		/*  Start reading data */
		data_in = 0;
		data_out = devpriv->ulConvertionRate;
		udelay(1);
		for (i = 0; i < 32; i++) {
			/*  Set the clock low */
			outb(0, dev->iobase + MPC624_ADC);
			udelay(1);

			if (data_out & (1 << 31)) {	/*  the next bit is a 1 */
				/*  Set the ADSDI line (send to MPC624) */
				outb(MPC624_ADSDI, dev->iobase + MPC624_ADC);
				udelay(1);
				/*  Set the clock high */
				outb(MPC624_ADSCK | MPC624_ADSDI,
				     dev->iobase + MPC624_ADC);
			} else {	/*  the next bit is a 0 */

				/*  Set the ADSDI line (send to MPC624) */
				outb(0, dev->iobase + MPC624_ADC);
				udelay(1);
				/*  Set the clock high */
				outb(MPC624_ADSCK, dev->iobase + MPC624_ADC);
			}
			/*  Read ADSDO on high clock (receive from MPC624) */
			udelay(1);
			data_in <<= 1;
			data_in |=
			    (inb(dev->iobase + MPC624_ADC) & MPC624_ADSDO) >> 4;
			udelay(1);

			data_out <<= 1;
		}

		/*  Received 32-bit long value consist of: */
		/*    31: EOC (End Of Transmission) bit - should be 0 */
		/*    30: DMY (Dummy) bit               - should be 0 */
		/*    29: SIG (Sign) bit                - 1 if the voltage is positive, 0 if negative */
		/*    28: MSB (Most Significant Bit)    - the first bit of convertion result */
		/*    .... */
		/*    05: LSB (Least Significant Bit)   - the last bit of convertion result */
		/*    04: sub-LSB                       - sub-LSBs are basically noise, but when */
		/*    03: sub-LSB                         averaged properly, they can increase convertion */
		/*    02: sub-LSB                         precision up to 29 bits; they can be discarded */
		/*    01: sub-LSB                         without loss of resolution. */
		/*    00: sub-LSB */

		if (data_in & MPC624_EOC_BIT)
			printk("MPC624: EOC bit is set (data_in=%lu)!",
			       data_in);
		if (data_in & MPC624_DMY_BIT)
			printk("MPC624: DMY bit is set (data_in=%lu)!",
			       data_in);
		if (data_in & MPC624_SGN_BIT) {	/*  check the sign bit *//*  The voltage is positive */
			data_in &= 0x3FFFFFFF;	/*  EOC and DMY should be 0, but we will mask them out just to be sure */
			data[n] = data_in;	/*  comedi operates on unsigned numbers, so we don't clear the SGN bit */
			/*  SGN bit is still set! It's correct, since we're converting to unsigned. */
		} else {	/*  The voltage is negative */
			/*  data_in contains a number in 30-bit two's complement code and we must deal with it */
			data_in |= MPC624_SGN_BIT;
			data_in = ~data_in;
			data_in += 1;
			data_in &= ~(MPC624_EOC_BIT | MPC624_DMY_BIT);
			/*  clear EOC and DMY bits */
			data_in = 0x20000000 - data_in;
			data[n] = data_in;
		}
	}

	/*  Return the number of samples read/written */
	return n;
}