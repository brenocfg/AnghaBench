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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STATID ; 
 scalar_t__ VINT_EN ; 
 TYPE_1__* ca91cx42_bridge ; 
 int /*<<< orphan*/  iack_queue ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vme_int ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ca91cx42_generate_irq(int level, int statid)
{
	u32 tmp;

	/* Universe can only generate even vectors */
	if (statid & 1)
		return -EINVAL;

	mutex_lock(&(vme_int));

	tmp = ioread32(ca91cx42_bridge->base + VINT_EN);

	/* Set Status/ID */
	iowrite32(statid << 24, ca91cx42_bridge->base + STATID);

	/* Assert VMEbus IRQ */
	tmp = tmp | (1 << (level + 24));
	iowrite32(tmp, ca91cx42_bridge->base + VINT_EN);

	/* Wait for IACK */
	wait_event_interruptible(iack_queue, 0);

	/* Return interrupt to low state */
	tmp = ioread32(ca91cx42_bridge->base + VINT_EN);
	tmp = tmp & ~(1 << (level + 24));
	iowrite32(tmp, ca91cx42_bridge->base + VINT_EN);

	mutex_unlock(&(vme_int));

	return 0;
}