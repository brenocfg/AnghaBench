#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; } ;
struct TYPE_8__ {int /*<<< orphan*/  result; int /*<<< orphan*/  itn_id; int /*<<< orphan*/  host_no; } ;
struct TYPE_7__ {int /*<<< orphan*/  result; int /*<<< orphan*/  mid; int /*<<< orphan*/  itn_id; int /*<<< orphan*/  host_no; } ;
struct TYPE_6__ {int /*<<< orphan*/  rw; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_uaddr; int /*<<< orphan*/  len; int /*<<< orphan*/  uaddr; int /*<<< orphan*/  tag; int /*<<< orphan*/  result; int /*<<< orphan*/  itn_id; int /*<<< orphan*/  host_no; } ;
struct TYPE_9__ {TYPE_3__ it_nexus_rsp; TYPE_2__ tsk_mgmt_rsp; TYPE_1__ cmd_rsp; } ;
struct tgt_event {TYPE_5__ hdr; TYPE_4__ p; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TGT_UEVENT_CMD_RSP 130 
#define  TGT_UEVENT_IT_NEXUS_RSP 129 
#define  TGT_UEVENT_TSK_MGMT_RSP 128 
 int /*<<< orphan*/  eprintk (char*,int) ; 
 int scsi_tgt_kspace_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_tgt_kspace_it_nexus_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_tgt_kspace_tsk_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_recv_msg(struct tgt_event *ev)
{
	int err = 0;

	switch (ev->hdr.type) {
	case TGT_UEVENT_CMD_RSP:
		err = scsi_tgt_kspace_exec(ev->p.cmd_rsp.host_no,
					   ev->p.cmd_rsp.itn_id,
					   ev->p.cmd_rsp.result,
					   ev->p.cmd_rsp.tag,
					   ev->p.cmd_rsp.uaddr,
					   ev->p.cmd_rsp.len,
					   ev->p.cmd_rsp.sense_uaddr,
					   ev->p.cmd_rsp.sense_len,
					   ev->p.cmd_rsp.rw);
		break;
	case TGT_UEVENT_TSK_MGMT_RSP:
		err = scsi_tgt_kspace_tsk_mgmt(ev->p.tsk_mgmt_rsp.host_no,
					       ev->p.tsk_mgmt_rsp.itn_id,
					       ev->p.tsk_mgmt_rsp.mid,
					       ev->p.tsk_mgmt_rsp.result);
		break;
	case TGT_UEVENT_IT_NEXUS_RSP:
		err = scsi_tgt_kspace_it_nexus_rsp(ev->p.it_nexus_rsp.host_no,
						   ev->p.it_nexus_rsp.itn_id,
						   ev->p.it_nexus_rsp.result);
		break;
	default:
		eprintk("unknown type %d\n", ev->hdr.type);
		err = -EINVAL;
	}

	return err;
}