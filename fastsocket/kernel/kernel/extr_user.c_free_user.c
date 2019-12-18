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
struct user_struct {int /*<<< orphan*/  session_keyring; int /*<<< orphan*/  uid_keyring; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct user_struct*) ; 
 int /*<<< orphan*/  sched_destroy_user (struct user_struct*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uid_cachep ; 
 int /*<<< orphan*/  uid_hash_remove (struct user_struct*) ; 
 int /*<<< orphan*/  uidhash_lock ; 

__attribute__((used)) static void free_user(struct user_struct *up, unsigned long flags)
{
	uid_hash_remove(up);
	spin_unlock_irqrestore(&uidhash_lock, flags);
	sched_destroy_user(up);
	key_put(up->uid_keyring);
	key_put(up->session_keyring);
	kmem_cache_free(uid_cachep, up);
}