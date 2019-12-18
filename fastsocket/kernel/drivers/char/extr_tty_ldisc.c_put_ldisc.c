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
struct tty_ldisc_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  refcount; } ;
struct tty_ldisc {struct tty_ldisc_ops* ops; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tty_ldisc*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_ldisc_lock ; 

__attribute__((used)) static void put_ldisc(struct tty_ldisc *ld)
{
	unsigned long flags;

	if (WARN_ON_ONCE(!ld))
		return;

	/*
	 * If this is the last user, free the ldisc, and
	 * release the ldisc ops.
	 *
	 * We really want an "atomic_dec_and_lock_irqsave()",
	 * but we don't have it, so this does it by hand.
	 */
	local_irq_save(flags);
	if (atomic_dec_and_lock(&ld->users, &tty_ldisc_lock)) {
		struct tty_ldisc_ops *ldo = ld->ops;

		ldo->refcount--;
		module_put(ldo->owner);
		spin_unlock_irqrestore(&tty_ldisc_lock, flags);

		kfree(ld);
		return;
	}
	local_irq_restore(flags);
}