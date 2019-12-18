#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  imm_struct ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/ * imm_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_out (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int imm_send_command(struct scsi_cmnd *cmd)
{
	imm_struct *dev = imm_dev(cmd->device->host);
	int k;

	/* NOTE: IMM uses byte pairs */
	for (k = 0; k < cmd->cmd_len; k += 2)
		if (!imm_out(dev, &cmd->cmnd[k], 2))
			return 0;
	return 1;
}