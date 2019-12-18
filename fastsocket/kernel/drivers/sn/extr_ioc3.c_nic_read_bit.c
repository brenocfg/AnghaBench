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
struct ioc3_driver_data {TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  mcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mcr_pack (int,int) ; 
 int nic_wait (struct ioc3_driver_data*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nic_read_bit(struct ioc3_driver_data *idd)
{
	int result;
	unsigned long flags;

	local_irq_save(flags);
	writel(mcr_pack(6, 13), &idd->vma->mcr);
	result = nic_wait(idd);
	local_irq_restore(flags);

	udelay(500);

	return result;
}