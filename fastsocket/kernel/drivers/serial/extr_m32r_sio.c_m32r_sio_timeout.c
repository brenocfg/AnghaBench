#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int timeout; int /*<<< orphan*/  lock; } ;
struct uart_sio_port {int /*<<< orphan*/  timer; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOSTS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  m32r_sio_handle_port (struct uart_sio_port*,unsigned int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int sio_in (struct uart_sio_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m32r_sio_timeout(unsigned long data)
{
	struct uart_sio_port *up = (struct uart_sio_port *)data;
	unsigned int timeout;
	unsigned int sts;

	sts = sio_in(up, SIOSTS);
	if (sts & 0x5) {
		spin_lock(&up->port.lock);
		m32r_sio_handle_port(up, sts);
		spin_unlock(&up->port.lock);
	}

	timeout = up->port.timeout;
	timeout = timeout > 6 ? (timeout / 2 - 2) : 1;
	mod_timer(&up->timer, jiffies + timeout);
}