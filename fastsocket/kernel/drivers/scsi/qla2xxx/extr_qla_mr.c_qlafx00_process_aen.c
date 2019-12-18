#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int fw_tgt_reported; } ;
struct scsi_qla_host {int /*<<< orphan*/  host; int /*<<< orphan*/  device_flags; int /*<<< orphan*/  dpc_flags; TYPE_1__ flags; int /*<<< orphan*/  loop_state; int /*<<< orphan*/  loop_down_timer; } ;
struct TYPE_5__ {int evtcode; int* mbx; } ;
struct TYPE_6__ {TYPE_2__ aenfx; } ;
struct qla_work_evt {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLG_NO_CABLE ; 
 int FCH_EVT_LINKDOWN ; 
 int FCH_EVT_LINKUP ; 
 int FCH_EVT_VENDOR_UNIQUE ; 
 int /*<<< orphan*/  LOOP_RESYNC_NEEDED ; 
 int /*<<< orphan*/  LOOP_UP ; 
#define  QLAFX00_MBA_LINK_DOWN 130 
#define  QLAFX00_MBA_LINK_UP 129 
#define  QLAFX00_MBA_PORT_UPDATE 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_get_event_number () ; 
 int /*<<< orphan*/  fc_host_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qla2x00_mark_all_devices_lost (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qlafx00_tgt_detach (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qlafx00_process_aen(struct scsi_qla_host *vha, struct qla_work_evt *evt)
{
	int rval = 0;
	uint32_t aen_code, aen_data;

	aen_code = FCH_EVT_VENDOR_UNIQUE;
	aen_data = evt->u.aenfx.evtcode;

	switch (evt->u.aenfx.evtcode) {
	case QLAFX00_MBA_PORT_UPDATE:		/* Port database update */
		if (evt->u.aenfx.mbx[1] == 0) {
			if (evt->u.aenfx.mbx[2] == 1) {
				if (!vha->flags.fw_tgt_reported)
					vha->flags.fw_tgt_reported = 1;
				atomic_set(&vha->loop_down_timer, 0);
				atomic_set(&vha->loop_state, LOOP_UP);
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			} else if (evt->u.aenfx.mbx[2] == 2) {
				qlafx00_tgt_detach(vha, evt->u.aenfx.mbx[3]);
			}
		} else if (evt->u.aenfx.mbx[1] == 0xffff) {
			if (evt->u.aenfx.mbx[2] == 1) {
				if (!vha->flags.fw_tgt_reported)
					vha->flags.fw_tgt_reported = 1;
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			} else if (evt->u.aenfx.mbx[2] == 2) {
				vha->device_flags |= DFLG_NO_CABLE;
				qla2x00_mark_all_devices_lost(vha, 1);
			}
		}
		break;
	case QLAFX00_MBA_LINK_UP:
		aen_code = FCH_EVT_LINKUP;
		aen_data = 0;
		break;
	case QLAFX00_MBA_LINK_DOWN:
		aen_code = FCH_EVT_LINKDOWN;
		aen_data = 0;
		break;
	}

	fc_host_post_event(vha->host, fc_get_event_number(),
	    aen_code, aen_data);

	return rval;
}