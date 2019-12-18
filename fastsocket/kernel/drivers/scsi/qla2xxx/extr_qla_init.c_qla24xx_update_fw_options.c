#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/ * fw_seriallink_options24; } ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int BIT_0 ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_set_serdes_params (TYPE_1__*,int,int,int) ; 

void
qla24xx_update_fw_options(scsi_qla_host_t *vha)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA82XX(ha))
		return;

	/* Update Serial Link options. */
	if ((le16_to_cpu(ha->fw_seriallink_options24[0]) & BIT_0) == 0)
		return;

	rval = qla2x00_set_serdes_params(vha,
	    le16_to_cpu(ha->fw_seriallink_options24[1]),
	    le16_to_cpu(ha->fw_seriallink_options24[2]),
	    le16_to_cpu(ha->fw_seriallink_options24[3]));
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x0104,
		    "Unable to update Serial Link options (%x).\n", rval);
	}
}