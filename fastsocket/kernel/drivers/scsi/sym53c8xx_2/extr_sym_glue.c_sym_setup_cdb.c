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
struct sym_hcb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct sym_ccb {TYPE_2__ phys; int /*<<< orphan*/  cdb_buf; } ;
struct scsi_cmnd {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCB_BA (struct sym_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cdb_buf ; 
 int /*<<< orphan*/  cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sym_setup_cdb(struct sym_hcb *np, struct scsi_cmnd *cmd, struct sym_ccb *cp)
{
	memcpy(cp->cdb_buf, cmd->cmnd, cmd->cmd_len);

	cp->phys.cmd.addr = CCB_BA(cp, cdb_buf[0]);
	cp->phys.cmd.size = cpu_to_scr(cmd->cmd_len);

	return 0;
}