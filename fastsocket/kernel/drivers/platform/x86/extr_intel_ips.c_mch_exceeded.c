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
struct ips_driver {int mch_avg_temp; scalar_t__ mch_avg_power; scalar_t__ mch_power_limit; int /*<<< orphan*/  turbo_status_lock; TYPE_1__* limits; } ;
struct TYPE_2__ {int mch_temp_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool mch_exceeded(struct ips_driver *ips)
{
	unsigned long flags;
	bool ret = false;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);
	if (ips->mch_avg_temp > (ips->limits->mch_temp_limit * 100))
		ret = true;
	if (ips->mch_avg_power > ips->mch_power_limit)
		ret = true;
	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	return ret;
}