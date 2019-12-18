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
struct rc_dev {struct nvt_dev* priv; } ;
struct nvt_dev {int in_use; int /*<<< orphan*/  nvt_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvt_enable_cir (struct nvt_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nvt_open(struct rc_dev *dev)
{
	struct nvt_dev *nvt = dev->priv;
	unsigned long flags;

	spin_lock_irqsave(&nvt->nvt_lock, flags);
	nvt->in_use = true;
	nvt_enable_cir(nvt);
	spin_unlock_irqrestore(&nvt->nvt_lock, flags);

	return 0;
}