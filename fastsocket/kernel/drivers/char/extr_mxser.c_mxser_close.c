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
struct tty_struct {scalar_t__ index; struct mxser_port* driver_data; } ;
struct tty_port {int dummy; } ;
struct mxser_port {struct tty_port port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ MXSER_PORTS ; 
 int /*<<< orphan*/  mxser_close_port (struct tty_struct*,struct tty_port*) ; 
 int /*<<< orphan*/  mxser_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxser_close(struct tty_struct *tty, struct file *filp)
{
	struct mxser_port *info = tty->driver_data;
	struct tty_port *port = &info->port;

	if (tty->index == MXSER_PORTS)
		return;
	if (tty_port_close_start(port, tty, filp) == 0)
		return;
	mxser_close_port(tty, port);
	mxser_flush_buffer(tty);
	/* Right now the tty_port set is done outside of the close_end helper
	   as we don't yet have everyone using refcounts */	
	tty_port_close_end(port, tty);
	tty_port_tty_set(port, NULL);
}