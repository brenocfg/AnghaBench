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
struct scsi_qla_host {TYPE_1__* qla4_82xx_reg; int /*<<< orphan*/  response_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsp_q_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4_82xx_complete_iocb(struct scsi_qla_host *ha)
{
	writel(ha->response_out, &ha->qla4_82xx_reg->rsp_q_out);
	readl(&ha->qla4_82xx_reg->rsp_q_out);
}