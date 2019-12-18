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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp_info {int dummy; } ;

/* Variables and functions */
 int locked_disable_mdp_irq (struct mdp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int disable_mdp_irq(struct mdp_info *mdp, uint32_t mask)
{
	unsigned long irq_flags;
	int ret;

	spin_lock_irqsave(&mdp_lock, irq_flags);
	ret = locked_disable_mdp_irq(mdp, mask);
	spin_unlock_irqrestore(&mdp_lock, irq_flags);
	return ret;
}