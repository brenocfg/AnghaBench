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
struct dvb_ringbuffer {scalar_t__ pwrite; scalar_t__ pread; scalar_t__ size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */

ssize_t dvb_ringbuffer_avail(struct dvb_ringbuffer *rbuf)
{
	ssize_t avail;

	avail = rbuf->pwrite - rbuf->pread;
	if (avail < 0)
		avail += rbuf->size;
	return avail;
}