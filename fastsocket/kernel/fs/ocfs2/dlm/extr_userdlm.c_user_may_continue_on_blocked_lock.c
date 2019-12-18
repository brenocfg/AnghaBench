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
struct user_lock_res {int l_flags; int /*<<< orphan*/  l_blocking; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int USER_LOCK_BLOCKED ; 
 int user_highest_compat_lock_level (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
user_may_continue_on_blocked_lock(struct user_lock_res *lockres,
				  int wanted)
{
	BUG_ON(!(lockres->l_flags & USER_LOCK_BLOCKED));

	return wanted <= user_highest_compat_lock_level(lockres->l_blocking);
}