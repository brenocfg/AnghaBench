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
typedef  int u8 ;
struct srp_indirect_buf {int dummy; } ;
struct srp_direct_buf {int dummy; } ;
struct srp_cmd {int add_cdb_len; int buf_fmt; int /*<<< orphan*/  add_data; } ;
struct scsi_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  srp_rdma_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
#define  SRP_DATA_DESC_DIRECT 130 
#define  SRP_DATA_DESC_INDIRECT 129 
#define  SRP_NO_DATA_DESC 128 
 scalar_t__ data_out_desc_size (struct srp_cmd*) ; 
 int /*<<< orphan*/  eprintk (char*,int,int) ; 
 int srp_cmd_direction (struct srp_cmd*) ; 
 int srp_direct_data (struct scsi_cmnd*,struct srp_direct_buf*,int,int /*<<< orphan*/ ,int,int) ; 
 int srp_indirect_data (struct scsi_cmnd*,struct srp_cmd*,struct srp_indirect_buf*,int,int /*<<< orphan*/ ,int,int) ; 

int srp_transfer_data(struct scsi_cmnd *sc, struct srp_cmd *cmd,
		      srp_rdma_t rdma_io, int dma_map, int ext_desc)
{
	struct srp_direct_buf *md;
	struct srp_indirect_buf *id;
	enum dma_data_direction dir;
	int offset, err = 0;
	u8 format;

	offset = cmd->add_cdb_len * 4;

	dir = srp_cmd_direction(cmd);
	if (dir == DMA_FROM_DEVICE)
		offset += data_out_desc_size(cmd);

	if (dir == DMA_TO_DEVICE)
		format = cmd->buf_fmt >> 4;
	else
		format = cmd->buf_fmt & ((1U << 4) - 1);

	switch (format) {
	case SRP_NO_DATA_DESC:
		break;
	case SRP_DATA_DESC_DIRECT:
		md = (struct srp_direct_buf *)
			(cmd->add_data + offset);
		err = srp_direct_data(sc, md, dir, rdma_io, dma_map, ext_desc);
		break;
	case SRP_DATA_DESC_INDIRECT:
		id = (struct srp_indirect_buf *)
			(cmd->add_data + offset);
		err = srp_indirect_data(sc, cmd, id, dir, rdma_io, dma_map,
					ext_desc);
		break;
	default:
		eprintk("Unknown format %d %x\n", dir, format);
		err = -EINVAL;
	}

	return err;
}