#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {TYPE_1__* isp_ops; } ;
struct TYPE_22__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_20__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_21__ {TYPE_2__ b; } ;
struct TYPE_23__ {int flags; TYPE_3__ d_id; int /*<<< orphan*/  loop_id; } ;
typedef  TYPE_5__ fc_port_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* fabric_logout ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_1 ; 
 int FCF_ASYNC_SENT ; 
 int FCF_FCP2_DEVICE ; 
 scalar_t__ IS_ALOGIO_CAPABLE (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 scalar_t__ ql2xasynclogin ; 
 int qla2x00_fabric_login (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int qla2x00_get_port_database (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (TYPE_4__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int qla2x00_post_async_login_work (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_update_fcport (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2x00_fabric_dev_login(scsi_qla_host_t *vha, fc_port_t *fcport,
    uint16_t *next_loopid)
{
	int	rval;
	int	retry;
	uint8_t opts;
	struct qla_hw_data *ha = vha->hw;

	rval = QLA_SUCCESS;
	retry = 0;

	if (ql2xasynclogin && IS_ALOGIO_CAPABLE(ha)) {
		if (fcport->flags & FCF_ASYNC_SENT)
			return rval;
		fcport->flags |= FCF_ASYNC_SENT;
		rval = qla2x00_post_async_login_work(vha, fcport, NULL);
		if (!rval)
			return rval;
	}

	fcport->flags &= ~FCF_ASYNC_SENT;
	rval = qla2x00_fabric_login(vha, fcport, next_loopid);
	if (rval == QLA_SUCCESS) {
		/* Send an ADISC to FCP2 devices.*/
		opts = 0;
		if (fcport->flags & FCF_FCP2_DEVICE)
			opts |= BIT_1;
		rval = qla2x00_get_port_database(vha, fcport, opts);
		if (rval != QLA_SUCCESS) {
			ha->isp_ops->fabric_logout(vha, fcport->loop_id,
			    fcport->d_id.b.domain, fcport->d_id.b.area,
			    fcport->d_id.b.al_pa);
			qla2x00_mark_device_lost(vha, fcport, 1, 0);
		} else {
			qla2x00_update_fcport(vha, fcport);
		}
	} else {
		/* Retry Login. */
		qla2x00_mark_device_lost(vha, fcport, 1, 0);
	}

	return (rval);
}