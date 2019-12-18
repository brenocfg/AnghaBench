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
struct TYPE_2__ {int XferState; scalar_t__ StructType; } ;
struct hw_fib {TYPE_1__ header; } ;
struct fib {int done; int /*<<< orphan*/  event_lock; struct hw_fib* hw_fib_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdapterProcessed ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 scalar_t__ FIB_MAGIC ; 
 scalar_t__ FIB_MAGIC2 ; 
 scalar_t__ FIB_MAGIC2_64 ; 
 int /*<<< orphan*/  HostOwned ; 
 int /*<<< orphan*/  SentFromHost ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_dealloc (struct fib*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int aac_fib_complete(struct fib *fibptr)
{
	unsigned long flags;
	struct hw_fib * hw_fib = fibptr->hw_fib_va;

	/*
	 *	Check for a fib which has already been completed
	 */

	if (hw_fib->header.XferState == 0)
		return 0;
	/*
	 *	If we plan to do anything check the structure type first.
	 */

	if (hw_fib->header.StructType != FIB_MAGIC &&
	    hw_fib->header.StructType != FIB_MAGIC2 &&
	    hw_fib->header.StructType != FIB_MAGIC2_64)
		return -EINVAL;
	/*
	 *	This block completes a cdb which orginated on the host and we
	 *	just need to deallocate the cdb or reinit it. At this point the
	 *	command is complete that we had sent to the adapter and this
	 *	cdb could be reused.
	 */
	spin_lock_irqsave(&fibptr->event_lock, flags);
	if (fibptr->done == 2) {
		spin_unlock_irqrestore(&fibptr->event_lock, flags);
		return 0;
	}
	spin_unlock_irqrestore(&fibptr->event_lock, flags);

	if((hw_fib->header.XferState & cpu_to_le32(SentFromHost)) &&
		(hw_fib->header.XferState & cpu_to_le32(AdapterProcessed)))
	{
		fib_dealloc(fibptr);
	}
	else if(hw_fib->header.XferState & cpu_to_le32(SentFromHost))
	{
		/*
		 *	This handles the case when the host has aborted the I/O
		 *	to the adapter because the adapter is not responding
		 */
		fib_dealloc(fibptr);
	} else if(hw_fib->header.XferState & cpu_to_le32(HostOwned)) {
		fib_dealloc(fibptr);
	} else {
		BUG();
	}
	return 0;
}