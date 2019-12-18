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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {size_t* TrimSetpoint; } ;

/* Variables and functions */
 int EOS ; 
 int /*<<< orphan*/  SETVECT (int,int) ; 
 int /*<<< orphan*/  SendDAC (struct comedi_device*,int) ; 
 int WS1 ; 
 int WS3 ; 
 int XFIFO_0 ; 
 int XFIFO_1 ; 
 int XFIFO_2 ; 
 int XFIFO_3 ; 
 int XSD2 ; 
 TYPE_1__* devpriv ; 
 scalar_t__* trimchan ; 

__attribute__((used)) static void WriteTrimDAC(struct comedi_device *dev, uint8_t LogicalChan,
			 uint8_t DacData)
{
	uint32_t chan;

	/*  Save the new setpoint in case the application needs to read it back later. */
	devpriv->TrimSetpoint[LogicalChan] = (uint8_t) DacData;

	/*  Map logical channel number to physical channel number. */
	chan = (uint32_t) trimchan[LogicalChan];

	/* Set up TSL2 records for TrimDac write operation.  All slots shift
	 * 0xFF in from pulled-up SD3 so that the end of the slot sequence
	 * can be detected.
	 */

	SETVECT(2, XSD2 | XFIFO_1 | WS3);
	/* Slot 2: Send high uint8_t to target TrimDac. */
	SETVECT(3, XSD2 | XFIFO_0 | WS3);
	/* Slot 3: Send low uint8_t to target TrimDac. */
	SETVECT(4, XSD2 | XFIFO_3 | WS1);
	/* Slot 4: Send NOP high uint8_t to DAC0 to keep clock running. */
	SETVECT(5, XSD2 | XFIFO_2 | WS1 | EOS);
	/* Slot 5: Send NOP low  uint8_t to DAC0. */

	/* Construct and transmit target DAC's serial packet:
	 * ( 0000 AAAA ), ( DDDD DDDD ),( 0x00 ),( 0x00 ) where A<3:0> is the
	 * DAC channel's address, and D<7:0> is the DAC setpoint.  Append a
	 * WORD value (that writes a channel 0 NOP command to a non-existent
	 * main DAC channel) that serves to keep the clock running after the
	 * packet has been sent to the target DAC.
	 */

	/*  Address the DAC channel within the trimdac device. */
	SendDAC(dev, ((uint32_t) chan << 8)
		| (uint32_t) DacData);	/*  Include DAC setpoint data. */
}