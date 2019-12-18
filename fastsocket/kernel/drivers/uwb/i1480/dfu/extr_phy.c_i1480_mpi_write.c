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
struct TYPE_4__ {size_t wEvent; void* bEventType; } ;
struct i1480_evt_confirm {scalar_t__ bResultCode; TYPE_2__ rceb; } ;
struct TYPE_3__ {void* wCommand; void* bCommandType; } ;
struct i1480_cmd_mpi_write {int /*<<< orphan*/  data; void* size; TYPE_1__ rccb; } ;
struct i1480 {int /*<<< orphan*/  dev; struct i1480_evt_confirm* evt_buf; struct i1480_cmd_mpi_write* cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ UWB_RC_RES_SUCCESS ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void* i1480_CET_VS1 ; 
 size_t i1480_CMD_MPI_WRITE ; 
 int i1480_cmd (struct i1480*,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static
int i1480_mpi_write(struct i1480 *i1480, const void *data, size_t size)
{
	int result;
	struct i1480_cmd_mpi_write *cmd = i1480->cmd_buf;
	struct i1480_evt_confirm *reply = i1480->evt_buf;

	BUG_ON(size > 480);
	result = -ENOMEM;
	cmd->rccb.bCommandType = i1480_CET_VS1;
	cmd->rccb.wCommand = cpu_to_le16(i1480_CMD_MPI_WRITE);
	cmd->size = cpu_to_le16(size);
	memcpy(cmd->data, data, size);
	reply->rceb.bEventType = i1480_CET_VS1;
	reply->rceb.wEvent = i1480_CMD_MPI_WRITE;
	result = i1480_cmd(i1480, "MPI-WRITE", sizeof(*cmd) + size, sizeof(*reply));
	if (result < 0)
		goto out;
	if (reply->bResultCode != UWB_RC_RES_SUCCESS) {
		dev_err(i1480->dev, "MPI-WRITE: command execution failed: %d\n",
			reply->bResultCode);
		result = -EIO;
	}
out:
	return result;
}