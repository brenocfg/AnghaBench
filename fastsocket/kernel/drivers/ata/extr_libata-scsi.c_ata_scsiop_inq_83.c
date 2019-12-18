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

/* Variables and functions */
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int ATA_ID_PROD_LEN ; 
 int /*<<< orphan*/  ATA_ID_SERNO ; 
 int ATA_ID_SERNO_LEN ; 
 int /*<<< orphan*/  ata_id_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_83(struct ata_scsi_args *args, u8 *rbuf)
{
	const int sat_model_serial_desc_len = 68;
	int num;

	rbuf[1] = 0x83;			/* this page code */
	num = 4;

	/* piv=0, assoc=lu, code_set=ACSII, designator=vendor */
	rbuf[num + 0] = 2;
	rbuf[num + 3] = ATA_ID_SERNO_LEN;
	num += 4;
	ata_id_string(args->id, (unsigned char *) rbuf + num,
		      ATA_ID_SERNO, ATA_ID_SERNO_LEN);
	num += ATA_ID_SERNO_LEN;

	/* SAT defined lu model and serial numbers descriptor */
	/* piv=0, assoc=lu, code_set=ACSII, designator=t10 vendor id */
	rbuf[num + 0] = 2;
	rbuf[num + 1] = 1;
	rbuf[num + 3] = sat_model_serial_desc_len;
	num += 4;
	memcpy(rbuf + num, "ATA     ", 8);
	num += 8;
	ata_id_string(args->id, (unsigned char *) rbuf + num, ATA_ID_PROD,
		      ATA_ID_PROD_LEN);
	num += ATA_ID_PROD_LEN;
	ata_id_string(args->id, (unsigned char *) rbuf + num, ATA_ID_SERNO,
		      ATA_ID_SERNO_LEN);
	num += ATA_ID_SERNO_LEN;

	rbuf[3] = num - 4;    /* page len (assume less than 256 bytes) */
	return 0;
}