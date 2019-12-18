#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {scalar_t__ link_data_rate; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_8__ {scalar_t__ fp_speed; int /*<<< orphan*/ * port_name; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ fc_port_t ;

/* Variables and functions */
 scalar_t__ FCS_ONLINE ; 
 int /*<<< orphan*/  IS_IIDMA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ PORT_SPEED_UNKNOWN ; 
 int QLA_SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_get_link_speed_str (struct qla_hw_data*,scalar_t__) ; 
 int qla2x00_set_idma_speed (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_iidma_fcport(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int rval;
	uint16_t mb[4];
	struct qla_hw_data *ha = vha->hw;

	if (!IS_IIDMA_CAPABLE(ha))
		return;

	if (atomic_read(&fcport->state) != FCS_ONLINE)
		return;

	if (fcport->fp_speed == PORT_SPEED_UNKNOWN ||
	    fcport->fp_speed > ha->link_data_rate)
		return;

	rval = qla2x00_set_idma_speed(vha, fcport->loop_id, fcport->fp_speed,
	    mb);
	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_disc, vha, 0x2004,
		    "Unable to adjust iIDMA "
		    "%02x%02x%02x%02x%02x%02x%02x%02x -- %04x %x %04x "
		    "%04x.\n", fcport->port_name[0], fcport->port_name[1],
		    fcport->port_name[2], fcport->port_name[3],
		    fcport->port_name[4], fcport->port_name[5],
		    fcport->port_name[6], fcport->port_name[7], rval,
		    fcport->fp_speed, mb[0], mb[1]);
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2005,
		    "iIDMA adjusted to %s GB/s "
		    "on %02x%02x%02x%02x%02x%02x%02x%02x.\n",
		    qla2x00_get_link_speed_str(ha, fcport->fp_speed),
		    fcport->port_name[0], fcport->port_name[1],
		    fcport->port_name[2], fcport->port_name[3],
		    fcport->port_name[4], fcport->port_name[5],
		    fcport->port_name[6], fcport->port_name[7]);
	}
}