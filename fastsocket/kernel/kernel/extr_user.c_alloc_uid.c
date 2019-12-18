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
struct user_struct {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  session_keyring; int /*<<< orphan*/  uid_keyring; int /*<<< orphan*/  __count; int /*<<< orphan*/  uid; } ;
struct user_namespace {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct user_struct*) ; 
 struct user_struct* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_create_user (struct user_struct*) ; 
 int /*<<< orphan*/  sched_destroy_user (struct user_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_cachep ; 
 struct user_struct* uid_hash_find (int /*<<< orphan*/ ,struct hlist_head*) ; 
 int /*<<< orphan*/  uid_hash_insert (struct user_struct*,struct hlist_head*) ; 
 int /*<<< orphan*/  uidhash_lock ; 
 struct hlist_head* uidhashentry (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uids_mutex_lock () ; 
 int /*<<< orphan*/  uids_mutex_unlock () ; 
 scalar_t__ uids_user_create (struct user_struct*) ; 

struct user_struct *alloc_uid(struct user_namespace *ns, uid_t uid)
{
	struct hlist_head *hashent = uidhashentry(ns, uid);
	struct user_struct *up, *new;

	/* Make uid_hash_find() + uids_user_create() + uid_hash_insert()
	 * atomic.
	 */
	uids_mutex_lock();

	spin_lock_irq(&uidhash_lock);
	up = uid_hash_find(uid, hashent);
	spin_unlock_irq(&uidhash_lock);

	if (!up) {
		new = kmem_cache_zalloc(uid_cachep, GFP_KERNEL);
		if (!new)
			goto out_unlock;

		new->uid = uid;
		atomic_set(&new->__count, 1);

		if (sched_create_user(new) < 0)
			goto out_free_user;

		new->user_ns = get_user_ns(ns);

		if (uids_user_create(new))
			goto out_destoy_sched;

		/*
		 * Before adding this, check whether we raced
		 * on adding the same user already..
		 */
		spin_lock_irq(&uidhash_lock);
		up = uid_hash_find(uid, hashent);
		if (up) {
			/* This case is not possible when CONFIG_USER_SCHED
			 * is defined, since we serialize alloc_uid() using
			 * uids_mutex. Hence no need to call
			 * sched_destroy_user() or remove_user_sysfs_dir().
			 */
			key_put(new->uid_keyring);
			key_put(new->session_keyring);
			kmem_cache_free(uid_cachep, new);
		} else {
			uid_hash_insert(new, hashent);
			up = new;
		}
		spin_unlock_irq(&uidhash_lock);
	}

	uids_mutex_unlock();

	return up;

out_destoy_sched:
	sched_destroy_user(new);
	put_user_ns(new->user_ns);
out_free_user:
	kmem_cache_free(uid_cachep, new);
out_unlock:
	uids_mutex_unlock();
	return NULL;
}