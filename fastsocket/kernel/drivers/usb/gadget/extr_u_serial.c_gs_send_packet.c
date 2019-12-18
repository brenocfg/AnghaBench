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
struct gs_port {int /*<<< orphan*/  port_write_buf; } ;

/* Variables and functions */
 unsigned int gs_buf_data_avail (int /*<<< orphan*/ *) ; 
 unsigned int gs_buf_get (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static unsigned
gs_send_packet(struct gs_port *port, char *packet, unsigned size)
{
	unsigned len;

	len = gs_buf_data_avail(&port->port_write_buf);
	if (len < size)
		size = len;
	if (size != 0)
		size = gs_buf_get(&port->port_write_buf, packet, size);
	return size;
}