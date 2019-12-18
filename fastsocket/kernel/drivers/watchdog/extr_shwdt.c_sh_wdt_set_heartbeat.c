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

/* Variables and functions */
 int EINVAL ; 
 int heartbeat ; 
 int /*<<< orphan*/  shwdt_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sh_wdt_set_heartbeat(int t)
{
	unsigned long flags;

	if (unlikely(t < 1 || t > 3600)) /* arbitrary upper limit */
		return -EINVAL;

	spin_lock_irqsave(&shwdt_lock, flags);
	heartbeat = t;
	spin_unlock_irqrestore(&shwdt_lock, flags);
	return 0;
}