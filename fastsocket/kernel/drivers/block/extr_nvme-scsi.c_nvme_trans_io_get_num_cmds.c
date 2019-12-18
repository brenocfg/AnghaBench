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
typedef  int u32 ;
struct sg_io_hdr {scalar_t__ iovec_count; } ;
struct nvme_trans_io_cdb {int xfer_len; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 nvme_trans_io_get_num_cmds(struct sg_io_hdr *hdr,
					struct nvme_trans_io_cdb *cdb_info,
					u32 max_blocks)
{
	/* If using iovecs, send one nvme command per vector */
	if (hdr->iovec_count > 0)
		return hdr->iovec_count;
	else if (cdb_info->xfer_len > max_blocks)
		return ((cdb_info->xfer_len - 1) / max_blocks) + 1;
	else
		return 1;
}