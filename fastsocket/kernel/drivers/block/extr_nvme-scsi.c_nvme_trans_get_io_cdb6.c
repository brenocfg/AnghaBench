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
typedef  int /*<<< orphan*/  u8 ;
struct nvme_trans_io_cdb {int lba; scalar_t__ xfer_len; scalar_t__ prot_info; scalar_t__ fua; } ;

/* Variables and functions */
 int GET_U32_FROM_CDB (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_U8_FROM_CDB (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IO_6_CDB_LBA_MASK ; 
 int /*<<< orphan*/  IO_6_CDB_LBA_OFFSET ; 
 int /*<<< orphan*/  IO_6_CDB_TX_LEN_OFFSET ; 
 scalar_t__ IO_6_DEFAULT_TX_LEN ; 

__attribute__((used)) static inline void nvme_trans_get_io_cdb6(u8 *cmd,
					struct nvme_trans_io_cdb *cdb_info)
{
	cdb_info->fua = 0;
	cdb_info->prot_info = 0;
	cdb_info->lba = GET_U32_FROM_CDB(cmd, IO_6_CDB_LBA_OFFSET) &
					IO_6_CDB_LBA_MASK;
	cdb_info->xfer_len = GET_U8_FROM_CDB(cmd, IO_6_CDB_TX_LEN_OFFSET);

	/* sbc3r27 sec 5.32 - TRANSFER LEN of 0 implies a 256 Block transfer */
	if (cdb_info->xfer_len == 0)
		cdb_info->xfer_len = IO_6_DEFAULT_TX_LEN;
}