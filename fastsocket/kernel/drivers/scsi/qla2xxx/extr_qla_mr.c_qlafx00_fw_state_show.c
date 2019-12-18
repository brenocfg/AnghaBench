#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_10__ {TYPE_2__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_8__ {int /*<<< orphan*/  eeh_busy; } ;
struct TYPE_9__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla2x00_reset_active (TYPE_3__*) ; 
 int qlafx00_get_firmware_state (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 

uint32_t
qlafx00_fw_state_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int rval = QLA_FUNCTION_FAILED;
	uint32_t state[1];

	if (qla2x00_reset_active(vha))
		ql_log(ql_log_warn, vha, 0x70ce,
		    "ISP reset active.\n");
	else if (!vha->hw->flags.eeh_busy) {
		rval = qlafx00_get_firmware_state(vha, state);
	}
	if (rval != QLA_SUCCESS)
		memset(state, -1, sizeof(state));

	return state[0];
}