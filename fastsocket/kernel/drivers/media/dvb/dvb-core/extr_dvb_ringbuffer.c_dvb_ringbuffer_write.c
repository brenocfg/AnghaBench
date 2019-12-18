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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ringbuffer {size_t pwrite; size_t size; scalar_t__ data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

ssize_t dvb_ringbuffer_write(struct dvb_ringbuffer *rbuf, const u8 *buf, size_t len)
{
	size_t todo = len;
	size_t split;

	split = (rbuf->pwrite + len > rbuf->size) ? rbuf->size - rbuf->pwrite : 0;

	if (split > 0) {
		memcpy(rbuf->data+rbuf->pwrite, buf, split);
		buf += split;
		todo -= split;
		rbuf->pwrite = 0;
	}
	memcpy(rbuf->data+rbuf->pwrite, buf, todo);
	rbuf->pwrite = (rbuf->pwrite + todo) % rbuf->size;

	return len;
}