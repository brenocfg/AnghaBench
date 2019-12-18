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
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct iu_entry {int /*<<< orphan*/  ilist; struct srp_target* target; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_6__ {TYPE_3__ cmd; } ;
struct TYPE_8__ {TYPE_2__ srp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct iu_entry*,struct srp_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srp_iu_put (struct iu_entry*) ; 
 TYPE_4__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int ibmvstgt_eh_abort_handler(struct scsi_cmnd *sc)
{
	unsigned long flags;
	struct iu_entry *iue = (struct iu_entry *) sc->SCp.ptr;
	struct srp_target *target = iue->target;

	dprintk("%p %p %x\n", iue, target, vio_iu(iue)->srp.cmd.cdb[0]);

	spin_lock_irqsave(&target->lock, flags);
	list_del(&iue->ilist);
	spin_unlock_irqrestore(&target->lock, flags);

	srp_iu_put(iue);

	return 0;
}