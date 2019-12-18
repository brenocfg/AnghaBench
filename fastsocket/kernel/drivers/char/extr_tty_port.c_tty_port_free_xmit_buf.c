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
struct tty_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * xmit_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void tty_port_free_xmit_buf(struct tty_port *port)
{
	mutex_lock(&port->mutex);
	if (port->xmit_buf != NULL) {
		free_page((unsigned long)port->xmit_buf);
		port->xmit_buf = NULL;
	}
	mutex_unlock(&port->mutex);
}