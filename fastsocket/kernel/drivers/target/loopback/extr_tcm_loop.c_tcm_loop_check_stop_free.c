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
struct se_cmd {int se_cmd_flags; } ;

/* Variables and functions */
 int SCF_SCSI_TMR_CDB ; 
 int /*<<< orphan*/  transport_generic_free_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_loop_check_stop_free(struct se_cmd *se_cmd)
{
	/*
	 * Do not release struct se_cmd's containing a valid TMR
	 * pointer.  These will be released directly in tcm_loop_device_reset()
	 * with transport_generic_free_cmd().
	 */
	if (se_cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)
		return 0;
	/*
	 * Release the struct se_cmd, which will make a callback to release
	 * struct tcm_loop_cmd * in tcm_loop_deallocate_core_cmd()
	 */
	transport_generic_free_cmd(se_cmd, 0);
	return 1;
}