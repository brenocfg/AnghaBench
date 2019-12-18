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
typedef  scalar_t__ u64 ;
struct xpc_partition {int /*<<< orphan*/  nchannels_engaged; } ;
struct xpc_channel {size_t partid; int flags; scalar_t__ kthreads_idle_limit; int /*<<< orphan*/  lock; int /*<<< orphan*/  kthreads_assigned; int /*<<< orphan*/  number; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {void (* indicate_partition_disengaged ) (struct xpc_partition*) ;int /*<<< orphan*/  (* indicate_partition_engaged ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_DISCONNECTINGCALLOUT_MADE ; 
 int /*<<< orphan*/  XPC_DISCONNECT_CHANNEL (struct xpc_channel*,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ XPC_PACK_ARGS (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,void*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpLackOfResources ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_kthread_start ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

void
xpc_create_kthreads(struct xpc_channel *ch, int needed,
		    int ignore_disconnecting)
{
	unsigned long irq_flags;
	u64 args = XPC_PACK_ARGS(ch->partid, ch->number);
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	struct task_struct *kthread;
	void (*indicate_partition_disengaged) (struct xpc_partition *) =
		xpc_arch_ops.indicate_partition_disengaged;

	while (needed-- > 0) {

		/*
		 * The following is done on behalf of the newly created
		 * kthread. That kthread is responsible for doing the
		 * counterpart to the following before it exits.
		 */
		if (ignore_disconnecting) {
			if (!atomic_inc_not_zero(&ch->kthreads_assigned)) {
				/* kthreads assigned had gone to zero */
				BUG_ON(!(ch->flags &
					 XPC_C_DISCONNECTINGCALLOUT_MADE));
				break;
			}

		} else if (ch->flags & XPC_C_DISCONNECTING) {
			break;

		} else if (atomic_inc_return(&ch->kthreads_assigned) == 1 &&
			   atomic_inc_return(&part->nchannels_engaged) == 1) {
			xpc_arch_ops.indicate_partition_engaged(part);
		}
		(void)xpc_part_ref(part);
		xpc_msgqueue_ref(ch);

		kthread = kthread_run(xpc_kthread_start, (void *)args,
				      "xpc%02dc%d", ch->partid, ch->number);
		if (IS_ERR(kthread)) {
			/* the fork failed */

			/*
			 * NOTE: if (ignore_disconnecting &&
			 * !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) is true,
			 * then we'll deadlock if all other kthreads assigned
			 * to this channel are blocked in the channel's
			 * registerer, because the only thing that will unblock
			 * them is the xpDisconnecting callout that this
			 * failed kthread_run() would have made.
			 */

			if (atomic_dec_return(&ch->kthreads_assigned) == 0 &&
			    atomic_dec_return(&part->nchannels_engaged) == 0) {
				indicate_partition_disengaged(part);
			}
			xpc_msgqueue_deref(ch);
			xpc_part_deref(part);

			if (atomic_read(&ch->kthreads_assigned) <
			    ch->kthreads_idle_limit) {
				/*
				 * Flag this as an error only if we have an
				 * insufficient #of kthreads for the channel
				 * to function.
				 */
				spin_lock_irqsave(&ch->lock, irq_flags);
				XPC_DISCONNECT_CHANNEL(ch, xpLackOfResources,
						       &irq_flags);
				spin_unlock_irqrestore(&ch->lock, irq_flags);
			}
			break;
		}
	}
}