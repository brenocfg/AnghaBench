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
struct comedi_async {scalar_t__ buf_read_ptr; scalar_t__ prealloc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_read_alloc (struct comedi_async*,int) ; 
 int /*<<< orphan*/  comedi_buf_read_free (struct comedi_async*,int) ; 
 unsigned int comedi_buf_read_n_available (struct comedi_async*) ; 

int comedi_buf_get(struct comedi_async *async, short *x)
{
	unsigned int n = comedi_buf_read_n_available(async);

	if (n < sizeof(short))
		return 0;
	comedi_buf_read_alloc(async, sizeof(short));
	*x = *(short *)(async->prealloc_buf + async->buf_read_ptr);
	comedi_buf_read_free(async, sizeof(short));
	return 1;
}