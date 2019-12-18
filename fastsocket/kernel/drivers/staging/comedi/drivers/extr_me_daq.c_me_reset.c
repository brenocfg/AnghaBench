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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ control_2; scalar_t__ control_1; scalar_t__ dac_control; scalar_t__ me_regbase; } ;

/* Variables and functions */
 scalar_t__ ME_CONTROL_1 ; 
 scalar_t__ ME_CONTROL_2 ; 
 scalar_t__ ME_DAC_CONTROL ; 
 scalar_t__ ME_RESET_INTERRUPT ; 
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int me_reset(struct comedi_device *dev)
{
	/* Reset board */
	writew(0x00, dev_private->me_regbase + ME_CONTROL_1);
	writew(0x00, dev_private->me_regbase + ME_CONTROL_2);
	writew(0x00, dev_private->me_regbase + ME_RESET_INTERRUPT);
	writew(0x00, dev_private->me_regbase + ME_DAC_CONTROL);

	/* Save values in the board context */
	dev_private->dac_control = 0;
	dev_private->control_1 = 0;
	dev_private->control_2 = 0;

	return 0;
}