#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ErrorInfo {int CommandStatus; int ScsiStatus; } ;
struct CommandList {struct ErrorInfo* err_info; TYPE_2__* h; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  CMD_ABORTED 139 
#define  CMD_ABORT_FAILED 138 
#define  CMD_CONNECTION_LOST 137 
#define  CMD_DATA_OVERRUN 136 
#define  CMD_DATA_UNDERRUN 135 
#define  CMD_HARDWARE_ERR 134 
#define  CMD_INVALID 133 
#define  CMD_PROTOCOL_ERR 132 
#define  CMD_TARGET_STATUS 131 
#define  CMD_TIMEOUT 130 
#define  CMD_UNABORTABLE 129 
#define  CMD_UNSOLICITED_ABORT 128 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 

__attribute__((used)) static void hpsa_scsi_interpret_error(struct CommandList *cp)
{
	struct ErrorInfo *ei;
	struct device *d = &cp->h->pdev->dev;

	ei = cp->err_info;
	switch (ei->CommandStatus) {
	case CMD_TARGET_STATUS:
		dev_warn(d, "cmd %p has completed with errors\n", cp);
		dev_warn(d, "cmd %p has SCSI Status = %x\n", cp,
				ei->ScsiStatus);
		if (ei->ScsiStatus == 0)
			dev_warn(d, "SCSI status is abnormally zero.  "
			"(probably indicates selection timeout "
			"reported incorrectly due to a known "
			"firmware bug, circa July, 2001.)\n");
		break;
	case CMD_DATA_UNDERRUN: /* let mid layer handle it. */
			dev_info(d, "UNDERRUN\n");
		break;
	case CMD_DATA_OVERRUN:
		dev_warn(d, "cp %p has completed with data overrun\n", cp);
		break;
	case CMD_INVALID: {
		/* controller unfortunately reports SCSI passthru's
		 * to non-existent targets as invalid commands.
		 */
		dev_warn(d, "cp %p is reported invalid (probably means "
			"target device no longer present)\n", cp);
		/* print_bytes((unsigned char *) cp, sizeof(*cp), 1, 0);
		print_cmd(cp);  */
		}
		break;
	case CMD_PROTOCOL_ERR:
		dev_warn(d, "cp %p has protocol error \n", cp);
		break;
	case CMD_HARDWARE_ERR:
		/* cmd->result = DID_ERROR << 16; */
		dev_warn(d, "cp %p had hardware error\n", cp);
		break;
	case CMD_CONNECTION_LOST:
		dev_warn(d, "cp %p had connection lost\n", cp);
		break;
	case CMD_ABORTED:
		dev_warn(d, "cp %p was aborted\n", cp);
		break;
	case CMD_ABORT_FAILED:
		dev_warn(d, "cp %p reports abort failed\n", cp);
		break;
	case CMD_UNSOLICITED_ABORT:
		dev_warn(d, "cp %p aborted due to an unsolicited abort\n", cp);
		break;
	case CMD_TIMEOUT:
		dev_warn(d, "cp %p timed out\n", cp);
		break;
	case CMD_UNABORTABLE:
		dev_warn(d, "Command unabortable\n");
		break;
	default:
		dev_warn(d, "cp %p returned unknown status %x\n", cp,
				ei->CommandStatus);
	}
}