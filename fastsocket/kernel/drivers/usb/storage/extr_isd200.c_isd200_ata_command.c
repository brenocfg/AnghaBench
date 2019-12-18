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
typedef  union ata_cdb {int dummy; } ata_cdb ;
struct us_data {int /*<<< orphan*/ * extra; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 int /*<<< orphan*/  isd200_invoke_transport (struct us_data*,struct scsi_cmnd*,union ata_cdb*) ; 
 int isd200_scsi_to_ata (struct scsi_cmnd*,struct us_data*,union ata_cdb*) ; 
 int /*<<< orphan*/  isd200_srb_set_bufflen (struct scsi_cmnd*,int) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isd200_ata_command(struct scsi_cmnd *srb, struct us_data *us)
{
	int sendToTransport = 1, orig_bufflen;
	union ata_cdb ataCdb;

	/* Make sure driver was initialized */

	if (us->extra == NULL)
		US_DEBUGP("ERROR Driver not initialized\n");

	scsi_set_resid(srb, 0);
	/* scsi_bufflen might change in protocol translation to ata */
	orig_bufflen = scsi_bufflen(srb);
	sendToTransport = isd200_scsi_to_ata(srb, us, &ataCdb);

	/* send the command to the transport layer */
	if (sendToTransport)
		isd200_invoke_transport(us, srb, &ataCdb);

	isd200_srb_set_bufflen(srb, orig_bufflen);
}