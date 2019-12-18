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
struct qla_hw_data {int /*<<< orphan*/ * fw_options; } ;
struct TYPE_4__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_9 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql2xetsenable ; 
 int /*<<< orphan*/  qla2x00_set_fw_options (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
qla81xx_update_fw_options(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (!ql2xetsenable)
		return;

	/* Enable ETS Burst. */
	memset(ha->fw_options, 0, sizeof(ha->fw_options));
	ha->fw_options[2] |= BIT_9;
	qla2x00_set_fw_options(vha, ha->fw_options);
}