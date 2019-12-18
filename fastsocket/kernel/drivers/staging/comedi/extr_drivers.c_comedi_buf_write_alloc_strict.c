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
struct comedi_async {unsigned int buf_read_count; unsigned int prealloc_bufsz; unsigned int buf_write_alloc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_mb () ; 

unsigned int comedi_buf_write_alloc_strict(struct comedi_async *async,
					   unsigned int nbytes)
{
	unsigned int free_end = async->buf_read_count + async->prealloc_bufsz;

	if ((int)(async->buf_write_alloc_count + nbytes - free_end) > 0) {
		nbytes = 0;
	}
	async->buf_write_alloc_count += nbytes;
	/* barrier insures the read of buf_read_count above occurs before
	   we write data to the write-alloc'ed buffer space */
	smp_mb();
	return nbytes;
}