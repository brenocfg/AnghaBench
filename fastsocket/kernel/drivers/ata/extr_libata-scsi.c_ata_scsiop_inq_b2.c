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
struct ata_scsi_args {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ata_scsiop_inq_b2(struct ata_scsi_args *args, u8 *rbuf)
{
	/* SCSI Thin Provisioning VPD page: SBC-3 rev 22 or later */
	rbuf[1] = 0xb2;
	rbuf[3] = 0x4;
	rbuf[5] = 1 << 6;	/* TPWS */

	return 0;
}