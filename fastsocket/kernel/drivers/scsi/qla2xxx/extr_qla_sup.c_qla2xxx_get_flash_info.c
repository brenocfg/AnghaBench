#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA2031 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA25XX (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int qla2xxx_find_flt_start (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2xxx_get_fdt_info (TYPE_1__*) ; 
 int /*<<< orphan*/  qla2xxx_get_flt_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_get_idc_param (TYPE_1__*) ; 

int
qla2xxx_get_flash_info(scsi_qla_host_t *vha)
{
	int ret;
	uint32_t flt_addr;
	struct qla_hw_data *ha = vha->hw;

	if (!IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha))
		return QLA_SUCCESS;

	ret = qla2xxx_find_flt_start(vha, &flt_addr);
	if (ret != QLA_SUCCESS)
		return ret;

	qla2xxx_get_flt_info(vha, flt_addr);
	qla2xxx_get_fdt_info(vha);
	qla2xxx_get_idc_param(vha);

	return QLA_SUCCESS;
}