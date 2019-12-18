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
struct ioc3_driver_data {int /*<<< orphan*/  gpio_lock; TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpcr_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 

void ioc3_gpcr_set(struct ioc3_driver_data *idd, unsigned int val)
{
	unsigned long flags;
	spin_lock_irqsave(&idd->gpio_lock, flags);
	writel(val, &idd->vma->gpcr_s);
	spin_unlock_irqrestore(&idd->gpio_lock, flags);
}