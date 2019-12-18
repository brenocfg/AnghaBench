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
struct tty_struct {struct gs_port* driver_data; } ;
struct gs_port {int /*<<< orphan*/  port_lock; scalar_t__ port_usb; int /*<<< orphan*/  port_write_buf; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int gs_buf_put (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int gs_start_tx (struct gs_port*) ; 
 int /*<<< orphan*/  pr_vdebug (char*,int /*<<< orphan*/ ,struct tty_struct*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gs_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	struct gs_port	*port = tty->driver_data;
	unsigned long	flags;
	int		status;

	pr_vdebug("gs_write: ttyGS%d (%p) writing %d bytes\n",
			port->port_num, tty, count);

	spin_lock_irqsave(&port->port_lock, flags);
	if (count)
		count = gs_buf_put(&port->port_write_buf, buf, count);
	/* treat count == 0 as flush_chars() */
	if (port->port_usb)
		status = gs_start_tx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	return count;
}