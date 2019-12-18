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
struct slgt_info {int /*<<< orphan*/  task; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  bh_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rx_timeout(unsigned long context)
{
	struct slgt_info *info = (struct slgt_info*)context;
	unsigned long flags;

	DBGINFO(("%s rx_timeout\n", info->device_name));
	spin_lock_irqsave(&info->lock, flags);
	info->pending_bh |= BH_RECEIVE;
	spin_unlock_irqrestore(&info->lock, flags);
	bh_handler(&info->task);
}