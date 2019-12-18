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
struct rchan_buf {size_t subbufs_produced; size_t subbufs_consumed; } ;
struct rchan {size_t n_subbufs; struct rchan_buf** buf; } ;

/* Variables and functions */
 unsigned int NR_CPUS ; 

void relay_subbufs_consumed(struct rchan *chan,
			    unsigned int cpu,
			    size_t subbufs_consumed)
{
	struct rchan_buf *buf;

	if (!chan)
		return;

	if (cpu >= NR_CPUS || !chan->buf[cpu] ||
					subbufs_consumed > chan->n_subbufs)
		return;

	buf = chan->buf[cpu];
	if (subbufs_consumed > buf->subbufs_produced - buf->subbufs_consumed)
		buf->subbufs_consumed = buf->subbufs_produced;
	else
		buf->subbufs_consumed += subbufs_consumed;
}