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
struct ata_scsi_args {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ID_SERNO ; 
 int ATA_ID_SERNO_LEN ; 
 int /*<<< orphan*/  ata_id_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_80(struct ata_scsi_args *args, u8 *rbuf)
{
	const u8 hdr[] = {
		0,
		0x80,			/* this page code */
		0,
		ATA_ID_SERNO_LEN,	/* page len */
	};

	memcpy(rbuf, hdr, sizeof(hdr));
	ata_id_string(args->id, (unsigned char *) &rbuf[4],
		      ATA_ID_SERNO, ATA_ID_SERNO_LEN);
	return 0;
}