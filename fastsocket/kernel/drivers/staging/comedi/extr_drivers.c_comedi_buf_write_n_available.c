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
struct comedi_async {unsigned int buf_read_count; unsigned int prealloc_bufsz; unsigned int buf_write_alloc_count; int /*<<< orphan*/  subdevice; } ;

/* Variables and functions */
 unsigned int bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

unsigned int comedi_buf_write_n_available(struct comedi_async *async)
{
	unsigned int free_end;
	unsigned int nbytes;

	if (async == NULL)
		return 0;

	free_end = async->buf_read_count + async->prealloc_bufsz;
	nbytes = free_end - async->buf_write_alloc_count;
	nbytes -= nbytes % bytes_per_sample(async->subdevice);
	/* barrier insures the read of buf_read_count in this
	   query occurs before any following writes to the buffer which
	   might be based on the return value from this query.
	 */
	smp_mb();
	return nbytes;
}