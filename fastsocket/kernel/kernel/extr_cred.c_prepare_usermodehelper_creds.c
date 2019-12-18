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
struct thread_group_cred {int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;
struct cred {int /*<<< orphan*/  usage; int /*<<< orphan*/ * security; struct thread_group_cred* tgcred; int /*<<< orphan*/  jit_keyring; int /*<<< orphan*/ * request_key_auth; int /*<<< orphan*/ * thread_keyring; int /*<<< orphan*/  user; int /*<<< orphan*/  group_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KEY_REQKEY_DEFL_DEFAULT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cred_jar ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_cred ; 
 int /*<<< orphan*/  kdebug (char*,struct cred*) ; 
 struct cred* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thread_group_cred* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cred*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 scalar_t__ security_prepare_creds (struct cred*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cred_subscribers (struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_creds (struct cred*) ; 

struct cred *prepare_usermodehelper_creds(void)
{
#ifdef CONFIG_KEYS
	struct thread_group_cred *tgcred = NULL;
#endif
	struct cred *new;

#ifdef CONFIG_KEYS
	tgcred = kzalloc(sizeof(*new->tgcred), GFP_ATOMIC);
	if (!tgcred)
		return NULL;
#endif

	new = kmem_cache_alloc(cred_jar, GFP_ATOMIC);
	if (!new)
		return NULL;

	kdebug("prepare_usermodehelper_creds() alloc %p", new);

	memcpy(new, &init_cred, sizeof(struct cred));

	atomic_set(&new->usage, 1);
	set_cred_subscribers(new, 0);
	get_group_info(new->group_info);
	get_uid(new->user);

#ifdef CONFIG_KEYS
	new->thread_keyring = NULL;
	new->request_key_auth = NULL;
	new->jit_keyring = KEY_REQKEY_DEFL_DEFAULT;

	atomic_set(&tgcred->usage, 1);
	spin_lock_init(&tgcred->lock);
	new->tgcred = tgcred;
#endif

#ifdef CONFIG_SECURITY
	new->security = NULL;
#endif
	if (security_prepare_creds(new, &init_cred, GFP_ATOMIC) < 0)
		goto error;
	validate_creds(new);

	BUG_ON(atomic_read(&new->usage) != 1);
	return new;

error:
	put_cred(new);
	return NULL;
}