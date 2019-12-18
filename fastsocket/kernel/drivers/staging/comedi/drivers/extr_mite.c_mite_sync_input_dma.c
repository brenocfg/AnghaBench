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
struct mite_channel {int dummy; } ;
struct comedi_async {unsigned int buf_write_alloc_count; unsigned int buf_write_count; int scan_progress; int /*<<< orphan*/  events; int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  subdevice; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_BLOCK ; 
 int /*<<< orphan*/  COMEDI_CB_EOS ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 unsigned int cfc_bytes_per_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_async*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_async*,int) ; 
 unsigned int mite_bytes_written_to_memory_lb (struct mite_channel*) ; 
 unsigned int mite_bytes_written_to_memory_ub (struct mite_channel*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int mite_sync_input_dma(struct mite_channel *mite_chan,
			struct comedi_async *async)
{
	int count;
	unsigned int nbytes, old_alloc_count;
	const unsigned bytes_per_scan = cfc_bytes_per_scan(async->subdevice);

	old_alloc_count = async->buf_write_alloc_count;
	/*  write alloc as much as we can */
	comedi_buf_write_alloc(async, async->prealloc_bufsz);

	nbytes = mite_bytes_written_to_memory_lb(mite_chan);
	if ((int)(mite_bytes_written_to_memory_ub(mite_chan) -
		  old_alloc_count) > 0) {
		printk("mite: DMA overwrite of free area\n");
		async->events |= COMEDI_CB_OVERFLOW;
		return -1;
	}

	count = nbytes - async->buf_write_count;
	/* it's possible count will be negative due to
	 * conservative value returned by mite_bytes_written_to_memory_lb */
	if (count <= 0)
		return 0;

	comedi_buf_write_free(async, count);

	async->scan_progress += count;
	if (async->scan_progress >= bytes_per_scan) {
		async->scan_progress %= bytes_per_scan;
		async->events |= COMEDI_CB_EOS;
	}
	async->events |= COMEDI_CB_BLOCK;
	return 0;
}