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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct nvme_dev {TYPE_1__* bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int NVME_CC_ENABLE ; 
 int nvme_wait_ready (struct nvme_dev*,int /*<<< orphan*/ ,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_disable_ctrl(struct nvme_dev *dev, u64 cap)
{
	u32 cc = readl(&dev->bar->cc);

	if (cc & NVME_CC_ENABLE)
		writel(cc & ~NVME_CC_ENABLE, &dev->bar->cc);
	return nvme_wait_ready(dev, cap, false);
}