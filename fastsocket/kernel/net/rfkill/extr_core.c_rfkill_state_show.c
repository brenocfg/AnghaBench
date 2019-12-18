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
typedef  int /*<<< orphan*/  u32 ;
struct rfkill {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct rfkill* to_rfkill (struct device*) ; 
 int user_state_from_blocked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rfkill_state_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct rfkill *rfkill = to_rfkill(dev);
	unsigned long flags;
	u32 state;

	spin_lock_irqsave(&rfkill->lock, flags);
	state = rfkill->state;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	return sprintf(buf, "%d\n", user_state_from_blocked(state));
}