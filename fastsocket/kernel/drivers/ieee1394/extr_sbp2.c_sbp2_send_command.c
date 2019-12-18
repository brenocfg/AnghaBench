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
struct sbp2_lu {int dummy; } ;
struct sbp2_command_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ sbp2_create_command_orb (struct sbp2_lu*,struct sbp2_command_info*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sbp2_link_orb_command (struct sbp2_lu*,struct sbp2_command_info*) ; 
 struct sbp2_command_info* sbp2util_allocate_command_orb (struct sbp2_lu*,struct scsi_cmnd*,void (*) (struct scsi_cmnd*)) ; 

__attribute__((used)) static int sbp2_send_command(struct sbp2_lu *lu, struct scsi_cmnd *SCpnt,
			     void (*done)(struct scsi_cmnd *))
{
	struct sbp2_command_info *cmd;

	cmd = sbp2util_allocate_command_orb(lu, SCpnt, done);
	if (!cmd)
		return -EIO;

	if (sbp2_create_command_orb(lu, cmd, SCpnt))
		return -ENOMEM;

	sbp2_link_orb_command(lu, cmd);
	return 0;
}