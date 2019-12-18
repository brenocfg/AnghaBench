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
struct ni_gpct {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mite_chan; } ;
struct comedi_cmd {int flags; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WRITE ; 
 int EIO ; 
 int ni_tio_cmd_setup (struct ni_gpct*,struct comedi_async*) ; 
 int ni_tio_input_cmd (struct ni_gpct*,struct comedi_async*) ; 
 int ni_tio_output_cmd (struct ni_gpct*,struct comedi_async*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ni_tio_cmd(struct ni_gpct *counter, struct comedi_async *async)
{
	struct comedi_cmd *cmd = &async->cmd;
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&counter->lock, flags);
	if (counter->mite_chan == NULL) {
		printk
		    ("ni_tio: commands only supported with DMA.  Interrupt-driven commands not yet implemented.\n");
		retval = -EIO;
	} else {
		retval = ni_tio_cmd_setup(counter, async);
		if (retval == 0) {
			if (cmd->flags & CMDF_WRITE) {
				retval = ni_tio_output_cmd(counter, async);
			} else {
				retval = ni_tio_input_cmd(counter, async);
			}
		}
	}
	spin_unlock_irqrestore(&counter->lock, flags);
	return retval;
}