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
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_type; int /*<<< orphan*/ * vha; } ;
typedef  TYPE_1__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  FCS_UNCONFIGURED ; 
 int /*<<< orphan*/  FCT_UNKNOWN ; 
 int /*<<< orphan*/  FC_COS_UNSPECIFIED ; 
 int /*<<< orphan*/  FC_NO_LOOP_ID ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

fc_port_t *
qla2x00_alloc_fcport(scsi_qla_host_t *vha, gfp_t flags)
{
	fc_port_t *fcport;

	fcport = kzalloc(sizeof(fc_port_t), flags);
	if (!fcport)
		return NULL;

	/* Setup fcport template structure. */
	fcport->vha = vha;
	fcport->port_type = FCT_UNKNOWN;
	fcport->loop_id = FC_NO_LOOP_ID;
	qla2x00_set_fcport_state(fcport, FCS_UNCONFIGURED);
	fcport->supported_classes = FC_COS_UNSPECIFIED;

	return fcport;
}