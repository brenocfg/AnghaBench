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
struct ql_adapter {int /*<<< orphan*/  mpi_port_cfg_work; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int ql_mb_about_fw (struct ql_adapter*) ; 
 int ql_mb_get_fw_state (struct ql_adapter*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_8000_port_initialize(struct ql_adapter *qdev)
{
	int status;
	/*
	 * Get MPI firmware version for driver banner
	 * and ethool info.
	 */
	status = ql_mb_about_fw(qdev);
	if (status)
		goto exit;
	status = ql_mb_get_fw_state(qdev);
	if (status)
		goto exit;
	/* Wake up a worker to get/set the TX/RX frame sizes. */
	queue_delayed_work(qdev->workqueue, &qdev->mpi_port_cfg_work, 0);
exit:
	return status;
}