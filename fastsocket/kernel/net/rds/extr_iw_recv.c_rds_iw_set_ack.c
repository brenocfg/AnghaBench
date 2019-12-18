#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rds_iw_connection {int /*<<< orphan*/  i_ack_lock; int /*<<< orphan*/  i_ack_flags; int /*<<< orphan*/  i_ack_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACK_REQUESTED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rds_iw_set_ack(struct rds_iw_connection *ic, u64 seq,
				int ack_required)
{
	unsigned long flags;

	spin_lock_irqsave(&ic->i_ack_lock, flags);
	ic->i_ack_next = seq;
	if (ack_required)
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
	spin_unlock_irqrestore(&ic->i_ack_lock, flags);
}