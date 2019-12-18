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
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 

__attribute__((used)) static void das6402_ai_fifo_dregs(struct comedi_device *dev,
				  struct comedi_subdevice *s)
{
	while (1) {
		if (!(inb(dev->iobase + 8) & 0x01))
			return;
		comedi_buf_put(s->async, inw(dev->iobase));
	}
}