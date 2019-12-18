#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {struct cred* cred; } ;
struct cred {int /*<<< orphan*/ * security; TYPE_1__* tgcred; int /*<<< orphan*/  request_key_auth; int /*<<< orphan*/  thread_keyring; int /*<<< orphan*/  user; int /*<<< orphan*/  group_info; int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cred_jar ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdebug (char*,struct cred*) ; 
 int /*<<< orphan*/  key_get (int /*<<< orphan*/ ) ; 
 struct cred* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cred*,struct cred const*,int) ; 
 scalar_t__ security_prepare_creds (struct cred*,struct cred const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cred_subscribers (struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_creds (struct cred*) ; 
 int /*<<< orphan*/  validate_process_creds () ; 

struct cred *prepare_creds(void)
{
	struct task_struct *task = current;
	const struct cred *old;
	struct cred *new;

	validate_process_creds();

	new = kmem_cache_alloc(cred_jar, GFP_KERNEL);
	if (!new)
		return NULL;

	kdebug("prepare_creds() alloc %p", new);

	old = task->cred;
	memcpy(new, old, sizeof(struct cred));

	atomic_set(&new->usage, 1);
	set_cred_subscribers(new, 0);
	get_group_info(new->group_info);
	get_uid(new->user);

#ifdef CONFIG_KEYS
	key_get(new->thread_keyring);
	key_get(new->request_key_auth);
	atomic_inc(&new->tgcred->usage);
#endif

#ifdef CONFIG_SECURITY
	new->security = NULL;
#endif

	if (security_prepare_creds(new, old, GFP_KERNEL) < 0)
		goto error;
	validate_creds(new);
	return new;

error:
	abort_creds(new);
	return NULL;
}