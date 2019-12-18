#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct srp_target {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
struct scsi_cmnd {scalar_t__ result; TYPE_1__ SCp; } ;
struct iu_entry {int /*<<< orphan*/  ilist; struct srp_target* target; } ;
struct TYPE_8__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_6__ {TYPE_4__ cmd; } ;
struct TYPE_7__ {TYPE_2__ srp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARDWARE_ERROR ; 
 int /*<<< orphan*/  NO_SENSE ; 
 scalar_t__ SAM_STAT_GOOD ; 
 int /*<<< orphan*/  dprintk (char*,struct iu_entry*,struct srp_target*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eprintk (char*,struct iu_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvstgt_rdma ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  send_rsp (struct iu_entry*,struct scsi_cmnd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srp_iu_put (struct iu_entry*) ; 
 int srp_transfer_data (struct scsi_cmnd*,TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int ibmvstgt_cmd_done(struct scsi_cmnd *sc,
			     void (*done)(struct scsi_cmnd *))
{
	unsigned long flags;
	struct iu_entry *iue = (struct iu_entry *) sc->SCp.ptr;
	struct srp_target *target = iue->target;
	int err = 0;

	dprintk("%p %p %x %u\n", iue, target, vio_iu(iue)->srp.cmd.cdb[0],
		scsi_sg_count(sc));

	if (scsi_sg_count(sc))
		err = srp_transfer_data(sc, &vio_iu(iue)->srp.cmd, ibmvstgt_rdma, 1, 1);

	spin_lock_irqsave(&target->lock, flags);
	list_del(&iue->ilist);
	spin_unlock_irqrestore(&target->lock, flags);

	if (err|| sc->result != SAM_STAT_GOOD) {
		eprintk("operation failed %p %d %x\n",
			iue, sc->result, vio_iu(iue)->srp.cmd.cdb[0]);
		send_rsp(iue, sc, HARDWARE_ERROR, 0x00);
	} else
		send_rsp(iue, sc, NO_SENSE, 0x00);

	done(sc);
	srp_iu_put(iue);
	return 0;
}