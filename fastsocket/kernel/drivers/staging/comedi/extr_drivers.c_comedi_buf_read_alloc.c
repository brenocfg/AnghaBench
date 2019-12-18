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
struct comedi_async {unsigned int buf_read_alloc_count; unsigned int munge_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

unsigned comedi_buf_read_alloc(struct comedi_async *async, unsigned nbytes)
{
	if ((int)(async->buf_read_alloc_count + nbytes - async->munge_count) >
	    0) {
		nbytes = async->munge_count - async->buf_read_alloc_count;
	}
	async->buf_read_alloc_count += nbytes;
	/* barrier insures read of munge_count occurs before we actually read
	   data out of buffer */
	smp_rmb();
	return nbytes;
}