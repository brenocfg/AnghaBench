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
struct scsi_sense_hdr {int sense_key; int asc; int /*<<< orphan*/  ascq; int /*<<< orphan*/  response_code; } ;
struct scsi_disk {int dummy; } ;
struct scsi_cmnd {int result; unsigned char* cmnd; struct request* request; int /*<<< orphan*/  sense_buffer; } ;
struct request {int cmd_flags; int /*<<< orphan*/  rq_disk; } ;

/* Variables and functions */
#define  ABORTED_COMMAND 133 
 scalar_t__ DRIVER_SENSE ; 
#define  HARDWARE_ERROR 132 
#define  ILLEGAL_REQUEST 131 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MEDIUM_ERROR 130 
#define  NO_SENSE 129 
 scalar_t__ READ ; 
#define  RECOVERED_ERROR 128 
 int REQ_DISCARD ; 
 int /*<<< orphan*/  SCSI_LOG_HLCOMPLETE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SD_LBP_DISABLE ; 
 unsigned char UNMAP ; 
 unsigned char WRITE_SAME ; 
 unsigned char WRITE_SAME_16 ; 
 unsigned int blk_rq_bytes (struct request*) ; 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_command_normalize_sense (struct scsi_cmnd*,struct scsi_sense_hdr*) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_print_result (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_print_sense (char*,struct scsi_cmnd*) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int scsi_sense_is_deferred (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,unsigned int) ; 
 unsigned int sd_completed_bytes (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_config_discard (struct scsi_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dif_complete (struct scsi_cmnd*,unsigned int) ; 

__attribute__((used)) static int sd_done(struct scsi_cmnd *SCpnt)
{
	int result = SCpnt->result;
	unsigned int good_bytes = result ? 0 : scsi_bufflen(SCpnt);
	struct scsi_sense_hdr sshdr;
	struct scsi_disk *sdkp = scsi_disk(SCpnt->request->rq_disk);
	struct request *req = SCpnt->request;
	int sense_valid = 0;
	int sense_deferred = 0;
	unsigned char op = SCpnt->cmnd[0];

	if (req->cmd_flags & REQ_DISCARD) {
		if (!result) {
			good_bytes = blk_rq_bytes(req);
			scsi_set_resid(SCpnt, 0);
		} else {
			good_bytes = 0;
			scsi_set_resid(SCpnt, blk_rq_bytes(req));
		}
	}

	if (result) {
		sense_valid = scsi_command_normalize_sense(SCpnt, &sshdr);
		if (sense_valid)
			sense_deferred = scsi_sense_is_deferred(&sshdr);
	}
#ifdef CONFIG_SCSI_LOGGING
	SCSI_LOG_HLCOMPLETE(1, scsi_print_result(SCpnt));
	if (sense_valid) {
		SCSI_LOG_HLCOMPLETE(1, scmd_printk(KERN_INFO, SCpnt,
						   "sd_done: sb[respc,sk,asc,"
						   "ascq]=%x,%x,%x,%x\n",
						   sshdr.response_code,
						   sshdr.sense_key, sshdr.asc,
						   sshdr.ascq));
	}
#endif
	if (driver_byte(result) != DRIVER_SENSE &&
	    (!sense_valid || sense_deferred))
		goto out;

	switch (sshdr.sense_key) {
	case HARDWARE_ERROR:
	case MEDIUM_ERROR:
		good_bytes = sd_completed_bytes(SCpnt);
		break;
	case RECOVERED_ERROR:
		good_bytes = scsi_bufflen(SCpnt);
		break;
	case NO_SENSE:
		/* This indicates a false check condition, so ignore it.  An
		 * unknown amount of data was transferred so treat it as an
		 * error.
		 */
		scsi_print_sense("sd", SCpnt);
		SCpnt->result = 0;
		memset(SCpnt->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		break;
	case ABORTED_COMMAND:
		if (sshdr.asc == 0x10)  /* DIF: Target detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
		break;
	case ILLEGAL_REQUEST:
		if (sshdr.asc == 0x10)  /* DIX: Host detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
		/* INVALID COMMAND OPCODE or INVALID FIELD IN CDB */
		if ((sshdr.asc == 0x20 || sshdr.asc == 0x24) &&
		    (op == UNMAP || op == WRITE_SAME_16 || op == WRITE_SAME))
			sd_config_discard(sdkp, SD_LBP_DISABLE);
		break;
	default:
		break;
	}
 out:
	if (rq_data_dir(SCpnt->request) == READ && scsi_prot_sg_count(SCpnt))
		sd_dif_complete(SCpnt, good_bytes);

	return good_bytes;
}