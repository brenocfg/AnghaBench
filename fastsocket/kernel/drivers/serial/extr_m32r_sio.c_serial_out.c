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
struct uart_sio_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sio_out (int,int) ; 

__attribute__((used)) static void serial_out(struct uart_sio_port *up, int offset, int value)
{
	if (!offset)
		return;

	__sio_out(value, offset);
}