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
typedef  scalar_t__ u8 ;
struct tty_struct {int dummy; } ;
struct tty_port {int /*<<< orphan*/  open_wait; } ;
struct moxa_port {struct tty_port port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 scalar_t__ tty_port_carrier_raised (struct tty_port*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int moxa_block_till_ready(struct tty_struct *tty, struct file *filp,
			    struct moxa_port *ch)
{
	struct tty_port *port = &ch->port;
	DEFINE_WAIT(wait);
	int retval = 0;
	u8 dcd;

	while (1) {
		prepare_to_wait(&port->open_wait, &wait, TASK_INTERRUPTIBLE);
		if (tty_hung_up_p(filp)) {
#ifdef SERIAL_DO_RESTART
			retval = -ERESTARTSYS;
#else
			retval = -EAGAIN;
#endif
			break;
		}
		dcd = tty_port_carrier_raised(port);
		if (dcd)
			break;

		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}
		schedule();
	}
	finish_wait(&port->open_wait, &wait);

	return retval;
}