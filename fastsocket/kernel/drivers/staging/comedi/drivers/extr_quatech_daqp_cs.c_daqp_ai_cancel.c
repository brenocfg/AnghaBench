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
struct local_info_t {int /*<<< orphan*/  interrupt_mode; scalar_t__ stop; } ;
struct comedi_subdevice {scalar_t__ private; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAQP_COMMAND ; 
 int /*<<< orphan*/  DAQP_COMMAND_STOP ; 
 int EIO ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  semaphore ; 

__attribute__((used)) static int daqp_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct local_info_t *local = (struct local_info_t *)s->private;

	if (local->stop) {
		return -EIO;
	}

	outb(DAQP_COMMAND_STOP, dev->iobase + DAQP_COMMAND);

	/* flush any linguring data in FIFO - superfluous here */
	/* outb(DAQP_COMMAND_RSTF, dev->iobase+DAQP_COMMAND); */

	local->interrupt_mode = semaphore;

	return 0;
}