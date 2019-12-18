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
typedef  int /*<<< orphan*/  versions ;
typedef  int u8 ;
struct ata_scsi_args {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ID_FW_REV ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int TYPE_DISK ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 scalar_t__ ata_id_removeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_id_string (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,...) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_std(struct ata_scsi_args *args, u8 *rbuf)
{
	const u8 versions[] = {
		0x60,	/* SAM-3 (no version claimed) */

		0x03,
		0x20,	/* SBC-2 (no version claimed) */

		0x02,
		0x60	/* SPC-3 (no version claimed) */
	};
	u8 hdr[] = {
		TYPE_DISK,
		0,
		0x5,	/* claim SPC-3 version compatibility */
		2,
		95 - 4
	};

	VPRINTK("ENTER\n");

	/* set scsi removeable (RMB) bit per ata bit */
	if (ata_id_removeable(args->id))
		hdr[1] |= (1 << 7);

	memcpy(rbuf, hdr, sizeof(hdr));
	memcpy(&rbuf[8], "ATA     ", 8);
	ata_id_string(args->id, &rbuf[16], ATA_ID_PROD, 16);
	ata_id_string(args->id, &rbuf[32], ATA_ID_FW_REV, 4);

	if (rbuf[32] == 0 || rbuf[32] == ' ')
		memcpy(&rbuf[32], "n/a ", 4);

	memcpy(rbuf + 59, versions, sizeof(versions));

	return 0;
}