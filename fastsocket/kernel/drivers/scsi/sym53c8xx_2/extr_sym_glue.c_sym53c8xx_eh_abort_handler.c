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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_EH_ABORT ; 
 int sym_eh_handler (int /*<<< orphan*/ ,char*,struct scsi_cmnd*) ; 

__attribute__((used)) static int sym53c8xx_eh_abort_handler(struct scsi_cmnd *cmd)
{
	return sym_eh_handler(SYM_EH_ABORT, "ABORT", cmd);
}