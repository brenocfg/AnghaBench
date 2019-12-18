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
struct pcibus_info {int /*<<< orphan*/  pbi_lock; int /*<<< orphan*/  pbi_int_ate_resource; } ;

/* Variables and functions */
 int alloc_ate_resource (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pcibr_ate_alloc(struct pcibus_info *pcibus_info, int count)
{
	int status;
	unsigned long flags;

	spin_lock_irqsave(&pcibus_info->pbi_lock, flags);
	status = alloc_ate_resource(&pcibus_info->pbi_int_ate_resource, count);
	spin_unlock_irqrestore(&pcibus_info->pbi_lock, flags);

	return status;
}