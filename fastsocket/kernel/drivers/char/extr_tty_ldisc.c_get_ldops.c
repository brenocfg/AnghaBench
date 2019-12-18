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
struct tty_ldisc_ops {int /*<<< orphan*/  refcount; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 struct tty_ldisc_ops* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_lock ; 
 struct tty_ldisc_ops** tty_ldiscs ; 

__attribute__((used)) static struct tty_ldisc_ops *get_ldops(int disc)
{
	unsigned long flags;
	struct tty_ldisc_ops *ldops, *ret;

	spin_lock_irqsave(&tty_ldisc_lock, flags);
	ret = ERR_PTR(-EINVAL);
	ldops = tty_ldiscs[disc];
	if (ldops) {
		ret = ERR_PTR(-EAGAIN);
		if (try_module_get(ldops->owner)) {
			ldops->refcount++;
			ret = ldops;
		}
	}
	spin_unlock_irqrestore(&tty_ldisc_lock, flags);
	return ret;
}