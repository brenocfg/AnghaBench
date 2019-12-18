#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {int portnum; } ;
struct TYPE_4__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_IDC_DRV_PRESENCE ; 
 int QLA_SUCCESS ; 
 int QLA_TEST_FAILED ; 
 int /*<<< orphan*/  qla83xx_rd_reg (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
qla83xx_check_driver_presence(scsi_qla_host_t *vha)
{
	uint32_t drv_presence = 0;
	struct qla_hw_data *ha = vha->hw;

	qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
	if (drv_presence & (1 << ha->portnum))
		return QLA_SUCCESS;
	else
		return QLA_TEST_FAILED;
}