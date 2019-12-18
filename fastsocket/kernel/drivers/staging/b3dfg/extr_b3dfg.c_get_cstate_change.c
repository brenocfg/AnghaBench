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
struct b3dfg_dev {unsigned long cstate_tstamp; int /*<<< orphan*/  cstate_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long get_cstate_change(struct b3dfg_dev *fgdev)
{
	unsigned long flags, when;

	spin_lock_irqsave(&fgdev->cstate_lock, flags);
	when = fgdev->cstate_tstamp;
	spin_unlock_irqrestore(&fgdev->cstate_lock, flags);
	return when;
}