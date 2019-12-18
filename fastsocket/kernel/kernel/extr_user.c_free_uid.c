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
struct user_struct {int /*<<< orphan*/  __count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_user (struct user_struct*,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  uidhash_lock ; 

void free_uid(struct user_struct *up)
{
	unsigned long flags;

	if (!up)
		return;

	local_irq_save(flags);
	if (atomic_dec_and_lock(&up->__count, &uidhash_lock))
		free_user(up, flags);
	else
		local_irq_restore(flags);
}