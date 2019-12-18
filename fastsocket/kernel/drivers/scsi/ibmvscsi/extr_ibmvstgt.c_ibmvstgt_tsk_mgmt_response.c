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
struct TYPE_3__ {int tsk_mgmt_func; } ;
struct TYPE_4__ {TYPE_1__ tsk_mgmt; } ;
union viosrp_iu {TYPE_2__ srp; } ;
typedef  scalar_t__ u64 ;
struct iu_entry {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 unsigned char ABORTED_COMMAND ; 
 unsigned char NO_SENSE ; 
#define  SRP_TSK_ABORT_TASK 128 
 int /*<<< orphan*/  eprintk (char*,struct iu_entry*,int) ; 
 int /*<<< orphan*/  send_rsp (struct iu_entry*,int /*<<< orphan*/ *,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  srp_iu_put (struct iu_entry*) ; 
 union viosrp_iu* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int ibmvstgt_tsk_mgmt_response(struct Scsi_Host *shost,
				      u64 itn_id, u64 mid, int result)
{
	struct iu_entry *iue = (struct iu_entry *) ((void *) mid);
	union viosrp_iu *iu = vio_iu(iue);
	unsigned char status, asc;

	eprintk("%p %d\n", iue, result);
	status = NO_SENSE;
	asc = 0;

	switch (iu->srp.tsk_mgmt.tsk_mgmt_func) {
	case SRP_TSK_ABORT_TASK:
		asc = 0x14;
		if (result)
			status = ABORTED_COMMAND;
		break;
	default:
		break;
	}

	send_rsp(iue, NULL, status, asc);
	srp_iu_put(iue);

	return 0;
}