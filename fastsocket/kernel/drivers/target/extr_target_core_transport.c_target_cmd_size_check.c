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
struct TYPE_5__ {int block_size; } ;
struct se_device {TYPE_3__* transport; TYPE_2__ dev_attrib; } ;
struct se_cmd {unsigned int data_length; scalar_t__ data_direction; unsigned int residual_count; int /*<<< orphan*/  se_cmd_flags; int /*<<< orphan*/ * t_task_cdb; TYPE_1__* se_tfo; scalar_t__ unknown_data_length; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SCF_OVERFLOW_BIT ; 
 int /*<<< orphan*/  SCF_UNDERFLOW_BIT ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

sense_reason_t
target_cmd_size_check(struct se_cmd *cmd, unsigned int size)
{
	struct se_device *dev = cmd->se_dev;

	if (cmd->unknown_data_length) {
		cmd->data_length = size;
	} else if (size != cmd->data_length) {
		pr_warn("TARGET_CORE[%s]: Expected Transfer Length:"
			" %u does not match SCSI CDB Length: %u for SAM Opcode:"
			" 0x%02x\n", cmd->se_tfo->get_fabric_name(),
				cmd->data_length, size, cmd->t_task_cdb[0]);

		if (cmd->data_direction == DMA_TO_DEVICE) {
			pr_err("Rejecting underflow/overflow"
					" WRITE data\n");
			return TCM_INVALID_CDB_FIELD;
		}
		/*
		 * Reject READ_* or WRITE_* with overflow/underflow for
		 * type SCF_SCSI_DATA_CDB.
		 */
		if (dev->dev_attrib.block_size != 512)  {
			pr_err("Failing OVERFLOW/UNDERFLOW for LBA op"
				" CDB on non 512-byte sector setup subsystem"
				" plugin: %s\n", dev->transport->name);
			/* Returns CHECK_CONDITION + INVALID_CDB_FIELD */
			return TCM_INVALID_CDB_FIELD;
		}
		/*
		 * For the overflow case keep the existing fabric provided
		 * ->data_length.  Otherwise for the underflow case, reset
		 * ->data_length to the smaller SCSI expected data transfer
		 * length.
		 */
		if (size > cmd->data_length) {
			cmd->se_cmd_flags |= SCF_OVERFLOW_BIT;
			cmd->residual_count = (size - cmd->data_length);
		} else {
			cmd->se_cmd_flags |= SCF_UNDERFLOW_BIT;
			cmd->residual_count = (cmd->data_length - size);
			cmd->data_length = size;
		}
	}

	return 0;

}