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
struct user_struct {int dummy; } ;
struct user_namespace {int /*<<< orphan*/  kref; struct user_struct* creator; scalar_t__ uidhash_table; } ;
struct cred {int /*<<< orphan*/ * request_key_auth; int /*<<< orphan*/  group_info; scalar_t__ fsgid; scalar_t__ sgid; scalar_t__ egid; scalar_t__ gid; scalar_t__ fsuid; scalar_t__ suid; scalar_t__ euid; scalar_t__ uid; struct user_struct* user; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (scalar_t__) ; 
 int UIDHASH_SZ ; 
 struct user_struct* alloc_uid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_groups ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct user_namespace*) ; 
 struct user_namespace* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_group_info (int /*<<< orphan*/ ) ; 

int create_user_ns(struct cred *new)
{
	struct user_namespace *ns;
	struct user_struct *root_user;
	int n;

	ns = kmalloc(sizeof(struct user_namespace), GFP_KERNEL);
	if (!ns)
		return -ENOMEM;

	kref_init(&ns->kref);

	for (n = 0; n < UIDHASH_SZ; ++n)
		INIT_HLIST_HEAD(ns->uidhash_table + n);

	/* Alloc new root user.  */
	root_user = alloc_uid(ns, 0);
	if (!root_user) {
		kfree(ns);
		return -ENOMEM;
	}

	/* set the new root user in the credentials under preparation */
	ns->creator = new->user;
	new->user = root_user;
	new->uid = new->euid = new->suid = new->fsuid = 0;
	new->gid = new->egid = new->sgid = new->fsgid = 0;
	put_group_info(new->group_info);
	new->group_info = get_group_info(&init_groups);
#ifdef CONFIG_KEYS
	key_put(new->request_key_auth);
	new->request_key_auth = NULL;
#endif
	/* tgcred will be cleared in our caller bc CLONE_THREAD won't be set */

	/* alloc_uid() incremented the userns refcount.  Just set it to 1 */
	kref_set(&ns->kref, 1);

	return 0;
}