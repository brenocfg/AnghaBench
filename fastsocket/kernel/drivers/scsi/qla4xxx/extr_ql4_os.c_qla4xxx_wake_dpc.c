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
struct scsi_qla_host {int /*<<< orphan*/  dpc_work; scalar_t__ dpc_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (scalar_t__,int /*<<< orphan*/ *) ; 

void qla4xxx_wake_dpc(struct scsi_qla_host *ha)
{
	if (ha->dpc_thread)
		queue_work(ha->dpc_thread, &ha->dpc_work);
}