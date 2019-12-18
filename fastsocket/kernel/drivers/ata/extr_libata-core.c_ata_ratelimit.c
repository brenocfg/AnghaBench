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
 int HZ ; 
 int /*<<< orphan*/  ata_ratelimit_lock ; 
 scalar_t__ jiffies ; 
 scalar_t__ ratelimit_time ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

int ata_ratelimit(void)
{
	int rc;
	unsigned long flags;

	spin_lock_irqsave(&ata_ratelimit_lock, flags);

	if (time_after(jiffies, ratelimit_time)) {
		rc = 1;
		ratelimit_time = jiffies + (HZ/5);
	} else
		rc = 0;

	spin_unlock_irqrestore(&ata_ratelimit_lock, flags);

	return rc;
}