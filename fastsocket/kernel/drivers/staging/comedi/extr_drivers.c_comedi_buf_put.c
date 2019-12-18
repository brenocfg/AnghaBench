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
struct comedi_async {scalar_t__ buf_write_ptr; scalar_t__ prealloc_buf; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 unsigned int comedi_buf_write_alloc_strict (struct comedi_async*,int) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_async*,int) ; 

int comedi_buf_put(struct comedi_async *async, short x)
{
	unsigned int n = comedi_buf_write_alloc_strict(async, sizeof(short));

	if (n < sizeof(short)) {
		async->events |= COMEDI_CB_ERROR;
		return 0;
	}
	*(short *)(async->prealloc_buf + async->buf_write_ptr) = x;
	comedi_buf_write_free(async, sizeof(short));
	return 1;
}