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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct TYPE_2__ {int /*<<< orphan*/  adv_dvc_var; int /*<<< orphan*/  asc_dvc_var; } ;
struct asc_board {TYPE_1__ dvc_var; } ;

/* Variables and functions */
 scalar_t__ ASC_NARROW_BOARD (struct asc_board*) ; 
 int /*<<< orphan*/  advansys_narrow_slave_configure (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advansys_wide_slave_configure (struct scsi_device*,int /*<<< orphan*/ *) ; 
 struct asc_board* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advansys_slave_configure(struct scsi_device *sdev)
{
	struct asc_board *boardp = shost_priv(sdev->host);

	if (ASC_NARROW_BOARD(boardp))
		advansys_narrow_slave_configure(sdev,
						&boardp->dvc_var.asc_dvc_var);
	else
		advansys_wide_slave_configure(sdev,
						&boardp->dvc_var.adv_dvc_var);

	return 0;
}