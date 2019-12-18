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
typedef  int /*<<< orphan*/  u32 ;
struct rds_header {int dummy; } ;
struct rds_ext_header_rdma_dest {void* h_rdma_offset; void* h_rdma_rkey; } ;
typedef  int /*<<< orphan*/  ext_hdr ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_EXTHDR_RDMA_DEST ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int rds_message_add_extension (struct rds_header*,int /*<<< orphan*/ ,struct rds_ext_header_rdma_dest*,int) ; 

int rds_message_add_rdma_dest_extension(struct rds_header *hdr, u32 r_key, u32 offset)
{
	struct rds_ext_header_rdma_dest ext_hdr;

	ext_hdr.h_rdma_rkey = cpu_to_be32(r_key);
	ext_hdr.h_rdma_offset = cpu_to_be32(offset);
	return rds_message_add_extension(hdr, RDS_EXTHDR_RDMA_DEST, &ext_hdr, sizeof(ext_hdr));
}