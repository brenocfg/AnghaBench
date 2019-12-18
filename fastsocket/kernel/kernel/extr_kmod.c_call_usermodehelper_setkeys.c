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
struct thread_group_cred {int /*<<< orphan*/  session_keyring; } ;
struct subprocess_info {TYPE_1__* cred; } ;
struct key {int dummy; } ;
struct TYPE_2__ {struct thread_group_cred* tgcred; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  key_get (struct key*) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 

void call_usermodehelper_setkeys(struct subprocess_info *info,
				 struct key *session_keyring)
{
#ifdef CONFIG_KEYS
	struct thread_group_cred *tgcred = info->cred->tgcred;
	key_put(tgcred->session_keyring);
	tgcred->session_keyring = key_get(session_keyring);
#else
	BUG();
#endif
}