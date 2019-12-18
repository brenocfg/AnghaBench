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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {TYPE_1__* hw; } ;
struct rsp_que {int dummy; } ;
struct req_que {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int __qla2x00_marker (struct scsi_qla_host*,struct req_que*,struct rsp_que*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
qla2x00_marker(struct scsi_qla_host *vha, struct req_que *req,
		struct rsp_que *rsp, uint16_t loop_id, uint16_t lun,
		uint8_t type)
{
	int ret;
	unsigned long flags = 0;

	spin_lock_irqsave(&vha->hw->hardware_lock, flags);
	ret = __qla2x00_marker(vha, req, rsp, loop_id, lun, type);
	spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);

	return (ret);
}