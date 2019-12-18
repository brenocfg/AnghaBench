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
struct ohci_iso_recv {scalar_t__ released_bytes; scalar_t__ buf_stride; int block_reader; int nblocks; } ;
struct hpsb_iso_packet_info {scalar_t__ total_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ohci_iso_recv_release_block (struct ohci_iso_recv*,int) ; 

__attribute__((used)) static void ohci_iso_recv_bufferfill_release(struct ohci_iso_recv *recv,
					     struct hpsb_iso_packet_info *info)
{
	/* release the memory where the packet was */
	recv->released_bytes += info->total_len;

	/* have we released enough memory for one block? */
	while (recv->released_bytes > recv->buf_stride) {
		ohci_iso_recv_release_block(recv, recv->block_reader);
		recv->block_reader = (recv->block_reader + 1) % recv->nblocks;
		recv->released_bytes -= recv->buf_stride;
	}
}