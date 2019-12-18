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
struct rfkill {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_get_type_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rfkill* to_rfkill (struct device*) ; 
 int /*<<< orphan*/  user_state_from_blocked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfkill_dev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct rfkill *rfkill = to_rfkill(dev);
	unsigned long flags;
	u32 state;
	int error;

	error = add_uevent_var(env, "RFKILL_NAME=%s", rfkill->name);
	if (error)
		return error;
	error = add_uevent_var(env, "RFKILL_TYPE=%s",
			       rfkill_get_type_str(rfkill->type));
	if (error)
		return error;
	spin_lock_irqsave(&rfkill->lock, flags);
	state = rfkill->state;
	spin_unlock_irqrestore(&rfkill->lock, flags);
	error = add_uevent_var(env, "RFKILL_STATE=%d",
			       user_state_from_blocked(state));
	return error;
}