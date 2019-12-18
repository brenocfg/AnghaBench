#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct mite_channel {int dummy; } ;
struct TYPE_2__ {unsigned int stop_arg; scalar_t__ stop_src; } ;
struct comedi_async {unsigned int buf_read_alloc_count; unsigned int buf_read_count; int /*<<< orphan*/  events; TYPE_1__ cmd; int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  subdevice; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_BLOCK ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 scalar_t__ TRIG_COUNT ; 
 unsigned int cfc_bytes_per_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_read_alloc (struct comedi_async*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_read_free (struct comedi_async*,int) ; 
 unsigned int mite_bytes_read_from_memory_lb (struct mite_channel*) ; 
 unsigned int mite_bytes_read_from_memory_ub (struct mite_channel*) ; 
 int /*<<< orphan*/  printk (char*) ; 

int mite_sync_output_dma(struct mite_channel *mite_chan,
			 struct comedi_async *async)
{
	int count;
	u32 nbytes_ub, nbytes_lb;
	unsigned int old_alloc_count;
	u32 stop_count =
	    async->cmd.stop_arg * cfc_bytes_per_scan(async->subdevice);

	old_alloc_count = async->buf_read_alloc_count;
	/*  read alloc as much as we can */
	comedi_buf_read_alloc(async, async->prealloc_bufsz);
	nbytes_lb = mite_bytes_read_from_memory_lb(mite_chan);
	if (async->cmd.stop_src == TRIG_COUNT &&
	    (int)(nbytes_lb - stop_count) > 0)
		nbytes_lb = stop_count;
	nbytes_ub = mite_bytes_read_from_memory_ub(mite_chan);
	if (async->cmd.stop_src == TRIG_COUNT &&
	    (int)(nbytes_ub - stop_count) > 0)
		nbytes_ub = stop_count;
	if ((int)(nbytes_ub - old_alloc_count) > 0) {
		printk("mite: DMA underrun\n");
		async->events |= COMEDI_CB_OVERFLOW;
		return -1;
	}
	count = nbytes_lb - async->buf_read_count;
	if (count <= 0)
		return 0;

	if (count) {
		comedi_buf_read_free(async, count);
		async->events |= COMEDI_CB_BLOCK;
	}
	return 0;
}