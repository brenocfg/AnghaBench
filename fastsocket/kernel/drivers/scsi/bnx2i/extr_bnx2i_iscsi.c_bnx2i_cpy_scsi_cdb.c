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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct scsi_lun {int dummy; } ;
struct scsi_cmnd {int cmd_len; scalar_t__ cmnd; TYPE_1__* device; } ;
struct TYPE_6__ {scalar_t__ cdb; void** lun; } ;
struct bnx2i_cmd {TYPE_3__ req; TYPE_2__* scsi_cmd; } ;
typedef  int /*<<< orphan*/  dword ;
struct TYPE_5__ {int cmd_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 void* be32_to_cpu (int) ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,int) ; 

__attribute__((used)) static void bnx2i_cpy_scsi_cdb(struct scsi_cmnd *sc, struct bnx2i_cmd *cmd)
{
	u32 dword;
	int lpcnt;
	u8 *srcp;
	u32 *dstp;
	u32 scsi_lun[2];

	int_to_scsilun(sc->device->lun, (struct scsi_lun *) scsi_lun);
	cmd->req.lun[0] = be32_to_cpu(scsi_lun[0]);
	cmd->req.lun[1] = be32_to_cpu(scsi_lun[1]);

	lpcnt = cmd->scsi_cmd->cmd_len / sizeof(dword);
	srcp = (u8 *) sc->cmnd;
	dstp = (u32 *) cmd->req.cdb;
	while (lpcnt--) {
		memcpy(&dword, (const void *) srcp, 4);
		*dstp = cpu_to_be32(dword);
		srcp += 4;
		dstp++;
	}
	if (sc->cmd_len & 0x3) {
		dword = (u32) srcp[0] | ((u32) srcp[1] << 8);
		*dstp = cpu_to_be32(dword);
	}
}