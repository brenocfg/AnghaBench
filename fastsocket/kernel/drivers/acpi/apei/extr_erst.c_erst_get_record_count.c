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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  __erst_get_record_count () ; 
 scalar_t__ erst_disable ; 
 int /*<<< orphan*/  erst_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

ssize_t erst_get_record_count(void)
{
	ssize_t count;
	unsigned long flags;

	if (erst_disable)
		return -ENODEV;

	spin_lock_irqsave(&erst_lock, flags);
	count = __erst_get_record_count();
	spin_unlock_irqrestore(&erst_lock, flags);

	return count;
}