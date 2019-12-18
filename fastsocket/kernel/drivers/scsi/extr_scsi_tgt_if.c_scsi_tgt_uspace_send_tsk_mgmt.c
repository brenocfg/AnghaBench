#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_3__ {int host_no; int function; void* mid; int /*<<< orphan*/  lun; void* tag; void* itn_id; } ;
struct TYPE_4__ {TYPE_1__ tsk_mgmt_req; } ;
struct tgt_event {TYPE_2__ p; } ;
struct scsi_lun {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  TGT_KEVENT_TSK_MGMT_REQ ; 
 int /*<<< orphan*/  dprintk (char*,int,int,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  eprintk (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct scsi_lun*,int) ; 
 int /*<<< orphan*/  memset (struct tgt_event*,int /*<<< orphan*/ ,int) ; 
 int tgt_uspace_send_event (int /*<<< orphan*/ ,struct tgt_event*) ; 

int scsi_tgt_uspace_send_tsk_mgmt(int host_no, u64 itn_id, int function,
				  u64 tag, struct scsi_lun *scsilun, void *data)
{
	struct tgt_event ev;
	int err;

	memset(&ev, 0, sizeof(ev));
	ev.p.tsk_mgmt_req.host_no = host_no;
	ev.p.tsk_mgmt_req.itn_id = itn_id;
	ev.p.tsk_mgmt_req.function = function;
	ev.p.tsk_mgmt_req.tag = tag;
	memcpy(ev.p.tsk_mgmt_req.lun, scsilun, sizeof(ev.p.tsk_mgmt_req.lun));
	ev.p.tsk_mgmt_req.mid = (u64) (unsigned long) data;

	dprintk("%d %x %llx %llx\n", host_no, function, (unsigned long long) tag,
		(unsigned long long) ev.p.tsk_mgmt_req.mid);

	err = tgt_uspace_send_event(TGT_KEVENT_TSK_MGMT_REQ, &ev);
	if (err)
		eprintk("tx buf is full, could not send\n");

	return err;
}