#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct MPT2SAS_ADAPTER {scalar_t__ pending_io_count; size_t scsiio_depth; int /*<<< orphan*/  reset_wq; int /*<<< orphan*/  scsi_lookup_lock; TYPE_1__* scsi_lookup; } ;
struct TYPE_2__ {int cb_idx; } ;

/* Variables and functions */
 int CAN_SLEEP ; 
 int HZ ; 
 int MPI2_IOC_STATE_MASK ; 
 int MPI2_IOC_STATE_OPERATIONAL ; 
 int mpt2sas_base_get_iocstate (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
_wait_for_commands_to_complete(struct MPT2SAS_ADAPTER *ioc, int sleep_flag)
{
	u32 ioc_state;
	unsigned long flags;
	u16 i;

	ioc->pending_io_count = 0;
	if (sleep_flag != CAN_SLEEP)
		return;

	ioc_state = mpt2sas_base_get_iocstate(ioc, 0);
	if ((ioc_state & MPI2_IOC_STATE_MASK) != MPI2_IOC_STATE_OPERATIONAL)
		return;

	/* pending command count */
	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	for (i = 0; i < ioc->scsiio_depth; i++)
		if (ioc->scsi_lookup[i].cb_idx != 0xFF)
			ioc->pending_io_count++;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	if (!ioc->pending_io_count)
		return;

	/* wait for pending commands to complete */
	wait_event_timeout(ioc->reset_wq, ioc->pending_io_count == 0, 10 * HZ);
}