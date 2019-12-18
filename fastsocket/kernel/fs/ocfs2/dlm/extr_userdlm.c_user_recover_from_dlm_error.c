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
struct user_lock_res {int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_LOCK_BUSY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void user_recover_from_dlm_error(struct user_lock_res *lockres)
{
	spin_lock(&lockres->l_lock);
	lockres->l_flags &= ~USER_LOCK_BUSY;
	spin_unlock(&lockres->l_lock);
}