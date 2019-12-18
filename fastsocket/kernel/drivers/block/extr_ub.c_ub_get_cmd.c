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
struct ub_scsi_cmd {int dummy; } ;
struct ub_lun {int* cmda; struct ub_scsi_cmd* cmdv; } ;

/* Variables and functions */

__attribute__((used)) static struct ub_scsi_cmd *ub_get_cmd(struct ub_lun *lun)
{
	struct ub_scsi_cmd *ret;

	if (lun->cmda[0])
		return NULL;
	ret = &lun->cmdv[0];
	lun->cmda[0] = 1;
	return ret;
}