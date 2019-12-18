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
struct slgt_info {unsigned int tbuf_current; unsigned int tbuf_count; scalar_t__ tx_active; TYPE_1__* tbufs; } ;
struct TYPE_2__ {unsigned int buf_count; } ;

/* Variables and functions */
 unsigned int BIT0 ; 
 int /*<<< orphan*/  TDCSR ; 
 unsigned int desc_count (TYPE_1__) ; 
 unsigned int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tbuf_bytes(struct slgt_info *info)
{
	unsigned int total_count = 0;
	unsigned int i = info->tbuf_current;
	unsigned int reg_value;
	unsigned int count;
	unsigned int active_buf_count = 0;

	/*
	 * Add descriptor counts for all tx DMA buffers.
	 * If count is zero (cleared by DMA controller after read),
	 * the buffer is complete or is actively being read from.
	 *
	 * Record buf_count of last buffer with zero count starting
	 * from current ring position. buf_count is mirror
	 * copy of count and is not cleared by serial controller.
	 * If DMA controller is active, that buffer is actively
	 * being read so add to total.
	 */
	do {
		count = desc_count(info->tbufs[i]);
		if (count)
			total_count += count;
		else if (!total_count)
			active_buf_count = info->tbufs[i].buf_count;
		if (++i == info->tbuf_count)
			i = 0;
	} while (i != info->tbuf_current);

	/* read tx DMA status register */
	reg_value = rd_reg32(info, TDCSR);

	/* if tx DMA active, last zero count buffer is in use */
	if (reg_value & BIT0)
		total_count += active_buf_count;

	/* add tx FIFO count = reg_value[15..8] */
	total_count += (reg_value >> 8) & 0xff;

	/* if transmitter active add one byte for shift register */
	if (info->tx_active)
		total_count++;

	return total_count;
}