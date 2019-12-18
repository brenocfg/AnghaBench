#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int current_topology; int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  fc_vport; int /*<<< orphan*/  vp_err_state; int /*<<< orphan*/  loop_state; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int ISP_CFG_F ; 
 scalar_t__ LOOP_DEAD ; 
 scalar_t__ LOOP_DOWN ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  VP_ERR_PORTDWN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_vport_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_taskm ; 
 int qla24xx_modify_vp_config (TYPE_1__*) ; 

int
qla24xx_enable_vp(scsi_qla_host_t *vha)
{
	int ret;
	struct qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	/* Check if physical ha port is Up */
	if (atomic_read(&base_vha->loop_state) == LOOP_DOWN  ||
		atomic_read(&base_vha->loop_state) == LOOP_DEAD ||
		!(ha->current_topology & ISP_CFG_F)) {
		vha->vp_err_state =  VP_ERR_PORTDWN;
		fc_vport_set_state(vha->fc_vport, FC_VPORT_LINKDOWN);
		goto enable_failed;
	}

	/* Initialize the new vport unless it is a persistent port */
	mutex_lock(&ha->vport_lock);
	ret = qla24xx_modify_vp_config(vha);
	mutex_unlock(&ha->vport_lock);

	if (ret != QLA_SUCCESS) {
		fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		goto enable_failed;
	}

	ql_dbg(ql_dbg_taskm, vha, 0x801a,
	    "Virtual port with id: %d - Enabled.\n", vha->vp_idx);
	return 0;

enable_failed:
	ql_dbg(ql_dbg_taskm, vha, 0x801b,
	    "Virtual port with id: %d - Disabled.\n", vha->vp_idx);
	return 1;
}