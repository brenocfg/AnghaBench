#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cred {TYPE_1__* tgcred; void* thread_keyring; int /*<<< orphan*/  jit_keyring; int /*<<< orphan*/  cap_bset; int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_inheritable; int /*<<< orphan*/  securebits; int /*<<< orphan*/  group_info; int /*<<< orphan*/  user; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  gid; int /*<<< orphan*/  fsuid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {struct cred* replacement_session_keyring; } ;
struct TYPE_3__ {void* process_keyring; int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 TYPE_2__* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_uid (int /*<<< orphan*/ ) ; 
 void* key_get (void*) ; 
 int /*<<< orphan*/  security_transfer_creds (struct cred*,struct cred const*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

void key_replace_session_keyring(void)
{
	const struct cred *old;
	struct cred *new;

	if (!current->replacement_session_keyring)
		return;

	write_lock_irq(&tasklist_lock);
	new = current->replacement_session_keyring;
	current->replacement_session_keyring = NULL;
	write_unlock_irq(&tasklist_lock);

	if (!new)
		return;

	old = current_cred();
	new->  uid	= old->  uid;
	new-> euid	= old-> euid;
	new-> suid	= old-> suid;
	new->fsuid	= old->fsuid;
	new->  gid	= old->  gid;
	new-> egid	= old-> egid;
	new-> sgid	= old-> sgid;
	new->fsgid	= old->fsgid;
	new->user	= get_uid(old->user);
	new->group_info	= get_group_info(old->group_info);

	new->securebits	= old->securebits;
	new->cap_inheritable	= old->cap_inheritable;
	new->cap_permitted	= old->cap_permitted;
	new->cap_effective	= old->cap_effective;
	new->cap_bset		= old->cap_bset;

	new->jit_keyring	= old->jit_keyring;
	new->thread_keyring	= key_get(old->thread_keyring);
	new->tgcred->tgid	= old->tgcred->tgid;
	new->tgcred->process_keyring = key_get(old->tgcred->process_keyring);

	security_transfer_creds(new, old);

	commit_creds(new);
}