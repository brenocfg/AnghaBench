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
typedef  int uint32_t ;
struct scsi_qla_host {int func_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8XXX_CRB_DRV_STATE ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 int qla4_8xxx_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_8xxx_wr_direct (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
qla4_8xxx_set_qsnt_ready(struct scsi_qla_host *ha)
{
	uint32_t qsnt_state;

	qsnt_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_STATE);

	/*
	 * For ISP8324, drv_active register has 1 bit per function,
	 * shift 1 by func_num to set a bit for the function.
	 * For ISP8022, drv_active has 4 bits per function.
	 */
	if (is_qla8032(ha))
		qsnt_state |= (1 << ha->func_num);
	else
		qsnt_state |= (2 << (ha->func_num * 4));

	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_STATE, qsnt_state);
}