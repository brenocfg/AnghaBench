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
struct tty_port {unsigned char* xmit_buf; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int tty_port_alloc_xmit_buf(struct tty_port *port)
{
	/* We may sleep in get_zeroed_page() */
	mutex_lock(&port->mutex);
	if (port->xmit_buf == NULL)
		port->xmit_buf = (unsigned char *)get_zeroed_page(GFP_KERNEL);
	mutex_unlock(&port->mutex);
	if (port->xmit_buf == NULL)
		return -ENOMEM;
	return 0;
}