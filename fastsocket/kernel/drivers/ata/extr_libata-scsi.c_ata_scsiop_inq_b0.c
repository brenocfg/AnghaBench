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
typedef  int u16 ;
struct ata_scsi_args {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ ata_id_has_trim (int /*<<< orphan*/ ) ; 
 int ata_id_log2_per_physical_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int*) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_b0(struct ata_scsi_args *args, u8 *rbuf)
{
	u16 min_io_sectors;

	rbuf[1] = 0xb0;
	rbuf[3] = 0x3c;		/* required VPD size with unmap support */

	/*
	 * Optimal transfer length granularity.
	 *
	 * This is always one physical block, but for disks with a smaller
	 * logical than physical sector size we need to figure out what the
	 * latter is.
	 */
	min_io_sectors = 1 << ata_id_log2_per_physical_sector(args->id);
	put_unaligned_be16(min_io_sectors, &rbuf[6]);

	/*
	 * Optimal unmap granularity.
	 *
	 * The ATA spec doesn't even know about a granularity or alignment
	 * for the TRIM command.  We can leave away most of the unmap related
	 * VPD page entries, but we have specifify a granularity to signal
	 * that we support some form of unmap - in thise case via WRITE SAME
	 * with the unmap bit set.
	 */
	if (ata_id_has_trim(args->id)) {
		put_unaligned_be64(65535 * 512 / 8, &rbuf[36]);
		put_unaligned_be32(1, &rbuf[28]);
	}

	return 0;
}