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
struct key {long serial; } ;
struct cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; TYPE_2__* tgcred; } ;
struct TYPE_4__ {TYPE_1__* session_keyring; } ;
struct TYPE_3__ {long serial; } ;

/* Variables and functions */
 long EMLINK ; 
 long ENOKEY ; 
 long ENOMEM ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_IN_QUOTA ; 
 long PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 long commit_creds (struct cred*) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  current_is_single_threaded () ; 
 struct key* find_keyring_by_name (char const*,int) ; 
 long install_session_keyring_to_cred (struct cred*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_session_mutex ; 
 struct key* keyring_alloc (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cred* prepare_creds () ; 

long join_session_keyring(const char *name)
{
	const struct cred *old;
	struct cred *new;
	struct key *keyring;
	long ret, serial;

	/* only permit this if there's a single thread in the thread group -
	 * this avoids us having to adjust the creds on all threads and risking
	 * ENOMEM */
	if (!current_is_single_threaded())
		return -EMLINK;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;
	old = current_cred();

	/* if no name is provided, install an anonymous keyring */
	if (!name) {
		ret = install_session_keyring_to_cred(new, NULL);
		if (ret < 0)
			goto error;

		serial = new->tgcred->session_keyring->serial;
		ret = commit_creds(new);
		if (ret == 0)
			ret = serial;
		goto okay;
	}

	/* allow the user to join or create a named keyring */
	mutex_lock(&key_session_mutex);

	/* look for an existing keyring of this name */
	keyring = find_keyring_by_name(name, false);
	if (PTR_ERR(keyring) == -ENOKEY) {
		/* not found - try and create a new one */
		keyring = keyring_alloc(name, old->uid, old->gid, old,
					KEY_ALLOC_IN_QUOTA, NULL);
		if (IS_ERR(keyring)) {
			ret = PTR_ERR(keyring);
			goto error2;
		}
	} else if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto error2;
	}

	/* we've got a keyring - now to install it */
	ret = install_session_keyring_to_cred(new, keyring);
	if (ret < 0)
		goto error2;

	commit_creds(new);
	mutex_unlock(&key_session_mutex);

	ret = keyring->serial;
	key_put(keyring);
okay:
	return ret;

error2:
	mutex_unlock(&key_session_mutex);
error:
	abort_creds(new);
	return ret;
}