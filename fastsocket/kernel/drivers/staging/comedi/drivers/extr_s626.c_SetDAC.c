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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int Dacpol; } ;

/* Variables and functions */
 int EOS ; 
 int /*<<< orphan*/  SETVECT (int,int) ; 
 int /*<<< orphan*/  SendDAC (struct comedi_device*,int) ; 
 int WS1 ; 
 int WS2 ; 
 int WS3 ; 
 int XFIFO_0 ; 
 int XFIFO_1 ; 
 int XFIFO_2 ; 
 int XFIFO_3 ; 
 int XSD2 ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static void SetDAC(struct comedi_device *dev, uint16_t chan, short dacdata)
{
	register uint16_t signmask;
	register uint32_t WSImage;

	/*  Adjust DAC data polarity and set up Polarity Control Register */
	/*  image. */
	signmask = 1 << chan;
	if (dacdata < 0) {
		dacdata = -dacdata;
		devpriv->Dacpol |= signmask;
	} else
		devpriv->Dacpol &= ~signmask;

	/*  Limit DAC setpoint value to valid range. */
	if ((uint16_t) dacdata > 0x1FFF)
		dacdata = 0x1FFF;

	/* Set up TSL2 records (aka "vectors") for DAC update.  Vectors V2
	 * and V3 transmit the setpoint to the target DAC.  V4 and V5 send
	 * data to a non-existent TrimDac channel just to keep the clock
	 * running after sending data to the target DAC.  This is necessary
	 * to eliminate the clock glitch that would otherwise occur at the
	 * end of the target DAC's serial data stream.  When the sequence
	 * restarts at V0 (after executing V5), the gate array automatically
	 * disables gating for the DAC clock and all DAC chip selects.
	 */

	WSImage = (chan & 2) ? WS1 : WS2;
	/* Choose DAC chip select to be asserted. */
	SETVECT(2, XSD2 | XFIFO_1 | WSImage);
	/* Slot 2: Transmit high data byte to target DAC. */
	SETVECT(3, XSD2 | XFIFO_0 | WSImage);
	/* Slot 3: Transmit low data byte to target DAC. */
	SETVECT(4, XSD2 | XFIFO_3 | WS3);
	/* Slot 4: Transmit to non-existent TrimDac channel to keep clock */
	SETVECT(5, XSD2 | XFIFO_2 | WS3 | EOS);
	/* Slot 5: running after writing target DAC's low data byte. */

	/*  Construct and transmit target DAC's serial packet:
	 * ( A10D DDDD ),( DDDD DDDD ),( 0x0F ),( 0x00 ) where A is chan<0>,
	 * and D<12:0> is the DAC setpoint.  Append a WORD value (that writes
	 * to a  non-existent TrimDac channel) that serves to keep the clock
	 * running after the packet has been sent to the target DAC.
	 */
	SendDAC(dev, 0x0F000000
		/* Continue clock after target DAC data (write to non-existent trimdac). */
		| 0x00004000
		/* Address the two main dual-DAC devices (TSL's chip select enables
		 * target device). */
		| ((uint32_t) (chan & 1) << 15)
		/*  Address the DAC channel within the  device. */
		| (uint32_t) dacdata);	/*  Include DAC setpoint data. */

}