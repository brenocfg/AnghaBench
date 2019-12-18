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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct dca_provider {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_tag ) (struct dca_provider*,struct device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct dca_provider* dca_find_provider_by_dev (struct device*) ; 
 int /*<<< orphan*/  dca_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dca_provider*,struct device*,int) ; 

u8 dca_common_get_tag(struct device *dev, int cpu)
{
	struct dca_provider *dca;
	u8 tag;
	unsigned long flags;

	spin_lock_irqsave(&dca_lock, flags);

	dca = dca_find_provider_by_dev(dev);
	if (!dca) {
		spin_unlock_irqrestore(&dca_lock, flags);
		return -ENODEV;
	}
	tag = dca->ops->get_tag(dca, dev, cpu);

	spin_unlock_irqrestore(&dca_lock, flags);
	return tag;
}