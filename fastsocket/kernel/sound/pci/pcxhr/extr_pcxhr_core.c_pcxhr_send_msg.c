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
struct pcxhr_rmh {int dummy; } ;
struct pcxhr_mgr {int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int pcxhr_send_msg_nolock (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pcxhr_send_msg(struct pcxhr_mgr *mgr, struct pcxhr_rmh *rmh)
{
	unsigned long flags;
	int err;
	spin_lock_irqsave(&mgr->msg_lock, flags);
	err = pcxhr_send_msg_nolock(mgr, rmh);
	spin_unlock_irqrestore(&mgr->msg_lock, flags);
	return err;
}