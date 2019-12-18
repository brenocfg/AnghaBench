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
typedef  int /*<<< orphan*/  uid_t ;
struct user_struct {int dummy; } ;
struct user_namespace {int dummy; } ;

/* Variables and functions */
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct user_struct* uid_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uidhash_lock ; 
 int /*<<< orphan*/  uidhashentry (struct user_namespace*,int /*<<< orphan*/ ) ; 

struct user_struct *find_user(uid_t uid)
{
	struct user_struct *ret;
	unsigned long flags;
	struct user_namespace *ns = current_user_ns();

	spin_lock_irqsave(&uidhash_lock, flags);
	ret = uid_hash_find(uid, uidhashentry(ns, uid));
	spin_unlock_irqrestore(&uidhash_lock, flags);
	return ret;
}