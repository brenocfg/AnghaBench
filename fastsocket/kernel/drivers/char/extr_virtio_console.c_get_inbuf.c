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
struct port_buffer {unsigned int len; scalar_t__ offset; } ;
struct TYPE_2__ {unsigned int bytes_received; } ;
struct port {TYPE_1__ stats; int /*<<< orphan*/  in_vq; struct port_buffer* inbuf; } ;

/* Variables and functions */
 struct port_buffer* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static struct port_buffer *get_inbuf(struct port *port)
{
	struct port_buffer *buf;
	unsigned int len;

	if (port->inbuf)
		return port->inbuf;

	buf = virtqueue_get_buf(port->in_vq, &len);
	if (buf) {
		buf->len = len;
		buf->offset = 0;
		port->stats.bytes_received += len;
	}
	return buf;
}