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
struct tty_struct {unsigned int index; int /*<<< orphan*/  flags; struct stliport* driver_data; } ;
struct tty_port {int flags; int /*<<< orphan*/  count; } ;
struct stliport {int devnr; struct tty_port port; int /*<<< orphan*/  raw_wait; int /*<<< orphan*/  state; } ;
struct stlibrd {int state; unsigned int nrports; struct stliport** ports; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int BST_STARTED ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 unsigned int MINOR2BRD (unsigned int) ; 
 unsigned int MINOR2PORT (unsigned int) ; 
 int /*<<< orphan*/  ST_INITIALIZING ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct stlibrd** stli_brds ; 
 int stli_initopen (struct tty_struct*,struct stlibrd*,struct stliport*) ; 
 unsigned int stli_nrbrds ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tty_port_block_til_ready (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stli_open(struct tty_struct *tty, struct file *filp)
{
	struct stlibrd *brdp;
	struct stliport *portp;
	struct tty_port *port;
	unsigned int minordev, brdnr, portnr;
	int rc;

	minordev = tty->index;
	brdnr = MINOR2BRD(minordev);
	if (brdnr >= stli_nrbrds)
		return -ENODEV;
	brdp = stli_brds[brdnr];
	if (brdp == NULL)
		return -ENODEV;
	if ((brdp->state & BST_STARTED) == 0)
		return -ENODEV;
	portnr = MINOR2PORT(minordev);
	if (portnr > brdp->nrports)
		return -ENODEV;

	portp = brdp->ports[portnr];
	if (portp == NULL)
		return -ENODEV;
	if (portp->devnr < 1)
		return -ENODEV;
	port = &portp->port;

/*
 *	On the first open of the device setup the port hardware, and
 *	initialize the per port data structure. Since initializing the port
 *	requires several commands to the board we will need to wait for any
 *	other open that is already initializing the port.
 *
 *	Review - locking
 */
	tty_port_tty_set(port, tty);
	tty->driver_data = portp;
	port->count++;

	wait_event_interruptible(portp->raw_wait,
			!test_bit(ST_INITIALIZING, &portp->state));
	if (signal_pending(current))
		return -ERESTARTSYS;

	if ((portp->port.flags & ASYNC_INITIALIZED) == 0) {
		set_bit(ST_INITIALIZING, &portp->state);
		if ((rc = stli_initopen(tty, brdp, portp)) >= 0) {
			/* Locking */
			port->flags |= ASYNC_INITIALIZED;
			clear_bit(TTY_IO_ERROR, &tty->flags);
		}
		clear_bit(ST_INITIALIZING, &portp->state);
		wake_up_interruptible(&portp->raw_wait);
		if (rc < 0)
			return rc;
	}
	return tty_port_block_til_ready(&portp->port, tty, filp);
}