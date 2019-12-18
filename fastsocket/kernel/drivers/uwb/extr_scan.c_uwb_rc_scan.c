#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int wEvent; void* bEventType; } ;
struct uwb_rc_evt_confirm {scalar_t__ bResultCode; TYPE_3__ rceb; } ;
struct TYPE_5__ {void* wCommand; void* bCommandType; } ;
struct uwb_rc_cmd_scan {unsigned int bChannelNumber; int bScanState; TYPE_2__ rccb; void* wStartTime; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct uwb_rc {unsigned int scanning; int scan_type; TYPE_1__ uwb_dev; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  enum uwb_scan_type { ____Placeholder_uwb_scan_type } uwb_scan_type ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* UWB_RC_CET_GENERAL ; 
 unsigned int UWB_RC_CMD_SCAN ; 
 scalar_t__ UWB_RC_RES_SUCCESS ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uwb_rc_cmd_scan*) ; 
 struct uwb_rc_cmd_scan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uwb_rc_cmd (struct uwb_rc*,char*,TYPE_2__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  uwb_rc_strerror (scalar_t__) ; 

int uwb_rc_scan(struct uwb_rc *rc,
		unsigned channel, enum uwb_scan_type type,
		unsigned bpst_offset)
{
	int result;
	struct uwb_rc_cmd_scan *cmd;
	struct uwb_rc_evt_confirm reply;

	result = -ENOMEM;
	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		goto error_kzalloc;
	mutex_lock(&rc->uwb_dev.mutex);
	cmd->rccb.bCommandType = UWB_RC_CET_GENERAL;
	cmd->rccb.wCommand = cpu_to_le16(UWB_RC_CMD_SCAN);
	cmd->bChannelNumber = channel;
	cmd->bScanState = type;
	cmd->wStartTime = cpu_to_le16(bpst_offset);
	reply.rceb.bEventType = UWB_RC_CET_GENERAL;
	reply.rceb.wEvent = UWB_RC_CMD_SCAN;
	result = uwb_rc_cmd(rc, "SCAN", &cmd->rccb, sizeof(*cmd),
			    &reply.rceb, sizeof(reply));
	if (result < 0)
		goto error_cmd;
	if (reply.bResultCode != UWB_RC_RES_SUCCESS) {
		dev_err(&rc->uwb_dev.dev,
			"SCAN: command execution failed: %s (%d)\n",
			uwb_rc_strerror(reply.bResultCode), reply.bResultCode);
		result = -EIO;
		goto error_cmd;
	}
	rc->scanning = channel;
	rc->scan_type = type;
error_cmd:
	mutex_unlock(&rc->uwb_dev.mutex);
	kfree(cmd);
error_kzalloc:
	return result;
}