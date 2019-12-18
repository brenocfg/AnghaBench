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
struct dvb_ringbuffer {scalar_t__ error; scalar_t__ pwrite; scalar_t__ pread; } ;

/* Variables and functions */

void dvb_ringbuffer_reset(struct dvb_ringbuffer *rbuf)
{
	rbuf->pread = rbuf->pwrite = 0;
	rbuf->error = 0;
}