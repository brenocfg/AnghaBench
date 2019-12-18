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
struct scsi_cmnd {int* cmnd; int result; } ;
struct ata_scsi_args {void (* done ) (struct scsi_cmnd*) ;struct scsi_cmnd* cmd; int /*<<< orphan*/  id; struct ata_device* dev; } ;
struct ata_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int DRIVER_SENSE ; 
#define  FORMAT_UNIT 143 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  INQUIRY 142 
#define  MODE_SELECT 141 
#define  MODE_SELECT_10 140 
#define  MODE_SENSE 139 
#define  MODE_SENSE_10 138 
#define  READ_CAPACITY 137 
#define  REPORT_LUNS 136 
#define  REQUEST_SENSE 135 
#define  REZERO_UNIT 134 
 int const SAI_READ_CAPACITY_16 ; 
#define  SEEK_10 133 
#define  SEEK_6 132 
#define  SEND_DIAGNOSTIC 131 
#define  SERVICE_ACTION_IN 130 
#define  SYNCHRONIZE_CACHE 129 
#define  TEST_UNIT_READY 128 
 int /*<<< orphan*/  ata_scsi_invalid_field (struct scsi_cmnd*,void (*) (struct scsi_cmnd*)) ; 
 int /*<<< orphan*/  ata_scsi_rbuf_fill (struct ata_scsi_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_scsiop_inq_00 ; 
 int /*<<< orphan*/  ata_scsiop_inq_80 ; 
 int /*<<< orphan*/  ata_scsiop_inq_83 ; 
 int /*<<< orphan*/  ata_scsiop_inq_89 ; 
 int /*<<< orphan*/  ata_scsiop_inq_b0 ; 
 int /*<<< orphan*/  ata_scsiop_inq_b1 ; 
 int /*<<< orphan*/  ata_scsiop_inq_b2 ; 
 int /*<<< orphan*/  ata_scsiop_inq_std ; 
 int /*<<< orphan*/  ata_scsiop_mode_sense ; 
 int /*<<< orphan*/  ata_scsiop_noop ; 
 int /*<<< orphan*/  ata_scsiop_read_cap ; 
 int /*<<< orphan*/  ata_scsiop_report_luns ; 

void ata_scsi_simulate(struct ata_device *dev, struct scsi_cmnd *cmd,
		      void (*done)(struct scsi_cmnd *))
{
	struct ata_scsi_args args;
	const u8 *scsicmd = cmd->cmnd;
	u8 tmp8;

	args.dev = dev;
	args.id = dev->id;
	args.cmd = cmd;
	args.done = done;

	switch(scsicmd[0]) {
	/* TODO: worth improving? */
	case FORMAT_UNIT:
		ata_scsi_invalid_field(cmd, done);
		break;

	case INQUIRY:
		if (scsicmd[1] & 2)	           /* is CmdDt set?  */
			ata_scsi_invalid_field(cmd, done);
		else if ((scsicmd[1] & 1) == 0)    /* is EVPD clear? */
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_std);
		else switch (scsicmd[2]) {
		case 0x00:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_00);
			break;
		case 0x80:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_80);
			break;
		case 0x83:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_83);
			break;
		case 0x89:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_89);
			break;
		case 0xb0:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b0);
			break;
		case 0xb1:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b1);
			break;
		case 0xb2:
			ata_scsi_rbuf_fill(&args, ata_scsiop_inq_b2);
			break;
		default:
			ata_scsi_invalid_field(cmd, done);
			break;
		}
		break;

	case MODE_SENSE:
	case MODE_SENSE_10:
		ata_scsi_rbuf_fill(&args, ata_scsiop_mode_sense);
		break;

	case MODE_SELECT:	/* unconditionally return */
	case MODE_SELECT_10:	/* bad-field-in-cdb */
		ata_scsi_invalid_field(cmd, done);
		break;

	case READ_CAPACITY:
		ata_scsi_rbuf_fill(&args, ata_scsiop_read_cap);
		break;

	case SERVICE_ACTION_IN:
		if ((scsicmd[1] & 0x1f) == SAI_READ_CAPACITY_16)
			ata_scsi_rbuf_fill(&args, ata_scsiop_read_cap);
		else
			ata_scsi_invalid_field(cmd, done);
		break;

	case REPORT_LUNS:
		ata_scsi_rbuf_fill(&args, ata_scsiop_report_luns);
		break;

	case REQUEST_SENSE:
		ata_scsi_set_sense(cmd, 0, 0, 0);
		cmd->result = (DRIVER_SENSE << 24);
		done(cmd);
		break;

	/* if we reach this, then writeback caching is disabled,
	 * turning this into a no-op.
	 */
	case SYNCHRONIZE_CACHE:
		/* fall through */

	/* no-op's, complete with success */
	case REZERO_UNIT:
	case SEEK_6:
	case SEEK_10:
	case TEST_UNIT_READY:
		ata_scsi_rbuf_fill(&args, ata_scsiop_noop);
		break;

	case SEND_DIAGNOSTIC:
		tmp8 = scsicmd[1] & ~(1 << 3);
		if ((tmp8 == 0x4) && (!scsicmd[3]) && (!scsicmd[4]))
			ata_scsi_rbuf_fill(&args, ata_scsiop_noop);
		else
			ata_scsi_invalid_field(cmd, done);
		break;

	/* all other commands */
	default:
		ata_scsi_set_sense(cmd, ILLEGAL_REQUEST, 0x20, 0x0);
		/* "Invalid command operation code" */
		done(cmd);
		break;
	}
}