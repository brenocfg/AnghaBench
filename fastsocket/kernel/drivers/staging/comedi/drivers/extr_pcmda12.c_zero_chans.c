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
 int CHANS ; 
 int /*<<< orphan*/  LSB_PORT (int) ; 
 int /*<<< orphan*/  MSB_PORT (int) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zero_chans(struct comedi_device *dev)
{				/* sets up an
				   ASIC chip to defaults */
	int i;
	for (i = 0; i < CHANS; ++i) {
/*      /\* do this as one instruction?? *\/ */
/*      outw(0, LSB_PORT(chan)); */
		outb(0, LSB_PORT(i));
		outb(0, MSB_PORT(i));
	}
	inb(LSB_PORT(0));	/* update chans. */
}