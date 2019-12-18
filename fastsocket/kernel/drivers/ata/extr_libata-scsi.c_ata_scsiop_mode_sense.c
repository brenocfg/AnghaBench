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
typedef  int u8 ;
struct ata_scsi_args {TYPE_1__* cmd; int /*<<< orphan*/  id; struct ata_device* dev; } ;
struct ata_device {int flags; scalar_t__ multi_count; } ;
typedef  int /*<<< orphan*/  sat_blk_desc ;
struct TYPE_2__ {int* cmnd; } ;

/* Variables and functions */
#define  ALL_MPAGES 131 
 int ALL_SUB_MPAGES ; 
 int ATA_DFLAG_LBA48 ; 
 int ATA_DFLAG_PIO ; 
#define  CACHE_MPAGE 130 
#define  CONTROL_MPAGE 129 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int MODE_SENSE ; 
#define  RW_RECOVERY_MPAGE 128 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 scalar_t__ ata_dev_supports_fua (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_msense_caching (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ata_msense_ctl_mode (int*) ; 
 int /*<<< orphan*/  ata_msense_rw_recovery (int*) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static unsigned int ata_scsiop_mode_sense(struct ata_scsi_args *args, u8 *rbuf)
{
	struct ata_device *dev = args->dev;
	u8 *scsicmd = args->cmd->cmnd, *p = rbuf;
	const u8 sat_blk_desc[] = {
		0, 0, 0, 0,	/* number of blocks: sat unspecified */
		0,
		0, 0x2, 0x0	/* block length: 512 bytes */
	};
	u8 pg, spg;
	unsigned int ebd, page_control, six_byte;
	u8 dpofua;

	VPRINTK("ENTER\n");

	six_byte = (scsicmd[0] == MODE_SENSE);
	ebd = !(scsicmd[1] & 0x8);      /* dbd bit inverted == edb */
	/*
	 * LLBA bit in msense(10) ignored (compliant)
	 */

	page_control = scsicmd[2] >> 6;
	switch (page_control) {
	case 0: /* current */
		break;  /* supported */
	case 3: /* saved */
		goto saving_not_supp;
	case 1: /* changeable */
	case 2: /* defaults */
	default:
		goto invalid_fld;
	}

	if (six_byte)
		p += 4 + (ebd ? 8 : 0);
	else
		p += 8 + (ebd ? 8 : 0);

	pg = scsicmd[2] & 0x3f;
	spg = scsicmd[3];
	/*
	 * No mode subpages supported (yet) but asking for _all_
	 * subpages may be valid
	 */
	if (spg && (spg != ALL_SUB_MPAGES))
		goto invalid_fld;

	switch(pg) {
	case RW_RECOVERY_MPAGE:
		p += ata_msense_rw_recovery(p);
		break;

	case CACHE_MPAGE:
		p += ata_msense_caching(args->id, p);
		break;

	case CONTROL_MPAGE:
		p += ata_msense_ctl_mode(p);
		break;

	case ALL_MPAGES:
		p += ata_msense_rw_recovery(p);
		p += ata_msense_caching(args->id, p);
		p += ata_msense_ctl_mode(p);
		break;

	default:		/* invalid page code */
		goto invalid_fld;
	}

	dpofua = 0;
	if (ata_dev_supports_fua(args->id) && (dev->flags & ATA_DFLAG_LBA48) &&
	    (!(dev->flags & ATA_DFLAG_PIO) || dev->multi_count))
		dpofua = 1 << 4;

	if (six_byte) {
		rbuf[0] = p - rbuf - 1;
		rbuf[2] |= dpofua;
		if (ebd) {
			rbuf[3] = sizeof(sat_blk_desc);
			memcpy(rbuf + 4, sat_blk_desc, sizeof(sat_blk_desc));
		}
	} else {
		unsigned int output_len = p - rbuf - 2;

		rbuf[0] = output_len >> 8;
		rbuf[1] = output_len;
		rbuf[3] |= dpofua;
		if (ebd) {
			rbuf[7] = sizeof(sat_blk_desc);
			memcpy(rbuf + 8, sat_blk_desc, sizeof(sat_blk_desc));
		}
	}
	return 0;

invalid_fld:
	ata_scsi_set_sense(args->cmd, ILLEGAL_REQUEST, 0x24, 0x0);
	/* "Invalid field in cbd" */
	return 1;

saving_not_supp:
	ata_scsi_set_sense(args->cmd, ILLEGAL_REQUEST, 0x39, 0x0);
	 /* "Saving parameters not supported" */
	return 1;
}