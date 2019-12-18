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
struct scsi_cmnd {char* cmnd; int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct fib {int dummy; } ;
struct aac_get_serial_resp {int /*<<< orphan*/  uid; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  sp ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int COMMAND_COMPLETE ; 
 scalar_t__ CT_OK ; 
 int DID_OK ; 
 char INQD_PDT_DA ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_valid_context (struct scsi_cmnd*,struct fib*) ; 
 scalar_t__ fib_data (struct fib*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,char*,int) ; 
 char snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void get_container_serial_callback(void *context, struct fib * fibptr)
{
	struct aac_get_serial_resp * get_serial_reply;
	struct scsi_cmnd * scsicmd;

	BUG_ON(fibptr == NULL);

	scsicmd = (struct scsi_cmnd *) context;
	if (!aac_valid_context(scsicmd, fibptr))
		return;

	get_serial_reply = (struct aac_get_serial_resp *) fib_data(fibptr);
	/* Failure is irrelevant, using default value instead */
	if (le32_to_cpu(get_serial_reply->status) == CT_OK) {
		char sp[13];
		/* EVPD bit set */
		sp[0] = INQD_PDT_DA;
		sp[1] = scsicmd->cmnd[2];
		sp[2] = 0;
		sp[3] = snprintf(sp+4, sizeof(sp)-4, "%08X",
		  le32_to_cpu(get_serial_reply->uid));
		scsi_sg_copy_from_buffer(scsicmd, sp, sizeof(sp));
	}

	scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8 | SAM_STAT_GOOD;

	aac_fib_complete(fibptr);
	aac_fib_free(fibptr);
	scsicmd->scsi_done(scsicmd);
}