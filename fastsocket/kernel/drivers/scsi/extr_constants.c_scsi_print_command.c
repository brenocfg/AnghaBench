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
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  print_opcode_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 

void scsi_print_command(struct scsi_cmnd *cmd)
{
	int k;

	if (cmd->cmnd == NULL)
		return;

	scmd_printk(KERN_INFO, cmd, "CDB: ");
	print_opcode_name(cmd->cmnd, cmd->cmd_len);

	/* print out all bytes in cdb */
	printk(":");
	for (k = 0; k < cmd->cmd_len; ++k)
		printk(" %02x", cmd->cmnd[k]);
	printk("\n");
}