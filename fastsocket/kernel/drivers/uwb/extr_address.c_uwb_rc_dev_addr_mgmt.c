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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  wEvent; void* bEventType; } ;
struct uwb_rc_evt_dev_addr_mgmt {int bResultCode; TYPE_3__ rceb; } ;
struct TYPE_5__ {int /*<<< orphan*/  wCommand; void* bCommandType; } ;
struct uwb_rc_cmd_dev_addr_mgmt {int bmOperationType; TYPE_2__ rccb; int /*<<< orphan*/  baAddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* UWB_RC_CET_GENERAL ; 
 int /*<<< orphan*/  UWB_RC_CMD_DEV_ADDR_MGMT ; 
 int UWB_RC_RES_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct uwb_rc_cmd_dev_addr_mgmt*) ; 
 struct uwb_rc_cmd_dev_addr_mgmt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,size_t) ; 
 int uwb_rc_cmd (struct uwb_rc*,char*,TYPE_2__*,int,TYPE_3__*,int) ; 
 int uwb_rc_strerror (int) ; 

__attribute__((used)) static
int uwb_rc_dev_addr_mgmt(struct uwb_rc *rc,
			 u8 bmOperationType, const u8 *baAddr,
			 struct uwb_rc_evt_dev_addr_mgmt *reply)
{
	int result;
	struct uwb_rc_cmd_dev_addr_mgmt *cmd;

	result = -ENOMEM;
	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		goto error_kzalloc;
	cmd->rccb.bCommandType = UWB_RC_CET_GENERAL;
	cmd->rccb.wCommand = cpu_to_le16(UWB_RC_CMD_DEV_ADDR_MGMT);
	cmd->bmOperationType = bmOperationType;
	if (baAddr) {
		size_t size = 0;
		switch (bmOperationType >> 1) {
		case 0:	size = 2; break;
		case 1:	size = 6; break;
		default: BUG();
		}
		memcpy(cmd->baAddr, baAddr, size);
	}
	reply->rceb.bEventType = UWB_RC_CET_GENERAL;
	reply->rceb.wEvent = UWB_RC_CMD_DEV_ADDR_MGMT;
	result = uwb_rc_cmd(rc, "DEV-ADDR-MGMT",
			    &cmd->rccb, sizeof(*cmd),
			    &reply->rceb, sizeof(*reply));
	if (result < 0)
		goto error_cmd;
	if (result < sizeof(*reply)) {
		dev_err(&rc->uwb_dev.dev,
			"DEV-ADDR-MGMT: not enough data replied: "
			"%d vs %zu bytes needed\n", result, sizeof(*reply));
		result = -ENOMSG;
	} else if (reply->bResultCode != UWB_RC_RES_SUCCESS) {
		dev_err(&rc->uwb_dev.dev,
			"DEV-ADDR-MGMT: command execution failed: %s (%d)\n",
			uwb_rc_strerror(reply->bResultCode),
			reply->bResultCode);
		result = -EIO;
	} else
		result = 0;
error_cmd:
	kfree(cmd);
error_kzalloc:
	return result;
}