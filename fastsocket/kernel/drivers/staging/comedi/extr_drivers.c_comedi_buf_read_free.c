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
struct comedi_async {unsigned int buf_read_count; unsigned int buf_read_alloc_count; unsigned int buf_read_ptr; unsigned int prealloc_bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  smp_mb () ; 

unsigned comedi_buf_read_free(struct comedi_async *async, unsigned int nbytes)
{
	/*  barrier insures data has been read out of buffer before read count is incremented */
	smp_mb();
	if ((int)(async->buf_read_count + nbytes -
		  async->buf_read_alloc_count) > 0) {
		printk
		    ("comedi: attempted to read-free more bytes than have been read-allocated.\n");
		nbytes = async->buf_read_alloc_count - async->buf_read_count;
	}
	async->buf_read_count += nbytes;
	async->buf_read_ptr += nbytes;
	async->buf_read_ptr %= async->prealloc_bufsz;
	return nbytes;
}