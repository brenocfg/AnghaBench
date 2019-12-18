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
struct comedi_device {scalar_t__ iobase; TYPE_1__* subdevices; } ;
struct TYPE_2__ {int n_chan; } ;

/* Variables and functions */
 int MULTIQ3_AD_MUX_EN ; 
 int /*<<< orphan*/  MULTIQ3_BP_RESET ; 
 int /*<<< orphan*/  MULTIQ3_CLOCK_DATA ; 
 int /*<<< orphan*/  MULTIQ3_CLOCK_SETUP ; 
 int /*<<< orphan*/  MULTIQ3_CNTR_RESET ; 
 scalar_t__ MULTIQ3_CONTROL ; 
 int MULTIQ3_CONTROL_MUST ; 
 int /*<<< orphan*/  MULTIQ3_EFLAG_RESET ; 
 scalar_t__ MULTIQ3_ENC_CONTROL ; 
 scalar_t__ MULTIQ3_ENC_DATA ; 
 int /*<<< orphan*/  MULTIQ3_INPUT_SETUP ; 
 int /*<<< orphan*/  MULTIQ3_QUAD_X4 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void encoder_reset(struct comedi_device *dev)
{
	int chan;
	for (chan = 0; chan < dev->subdevices[4].n_chan; chan++) {
		int control =
		    MULTIQ3_CONTROL_MUST | MULTIQ3_AD_MUX_EN | (chan << 3);
		outw(control, dev->iobase + MULTIQ3_CONTROL);
		outb(MULTIQ3_EFLAG_RESET, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_BP_RESET, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_CLOCK_DATA, dev->iobase + MULTIQ3_ENC_DATA);
		outb(MULTIQ3_CLOCK_SETUP, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_INPUT_SETUP, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_QUAD_X4, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_CNTR_RESET, dev->iobase + MULTIQ3_ENC_CONTROL);
	}
}