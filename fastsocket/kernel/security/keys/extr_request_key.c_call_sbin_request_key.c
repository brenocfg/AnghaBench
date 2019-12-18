#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct key_construction {struct key* authkey; struct key* key; } ;
struct key {int serial; int /*<<< orphan*/  flags; } ;
struct cred {int fsuid; int fsgid; TYPE_4__* user; TYPE_3__* tgcred; TYPE_1__* thread_keyring; } ;
typedef  int key_serial_t ;
struct TYPE_8__ {struct key* session_keyring; } ;
struct TYPE_7__ {int /*<<< orphan*/  session_keyring; TYPE_2__* process_keyring; } ;
struct TYPE_6__ {int serial; } ;
struct TYPE_5__ {int serial; } ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_QUOTA_OVERRUN ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int call_usermodehelper_keys (char*,char**,char**,struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_request_key (struct key_construction*,int) ; 
 struct cred* current_cred () ; 
 struct cred* get_current_cred () ; 
 int install_user_keyrings () ; 
 int /*<<< orphan*/  kdebug (char*,int) ; 
 int /*<<< orphan*/  kenter (char*,int,int,char const*) ; 
 int key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 scalar_t__ key_validate (struct key*) ; 
 struct key* keyring_alloc (char*,int,int,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 struct key* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int call_sbin_request_key(struct key_construction *cons,
				 const char *op,
				 void *aux)
{
	const struct cred *cred = current_cred();
	key_serial_t prkey, sskey;
	struct key *key = cons->key, *authkey = cons->authkey, *keyring,
		*session;
	char *argv[9], *envp[3], uid_str[12], gid_str[12];
	char key_str[12], keyring_str[3][12];
	char desc[20];
	int ret, i;

	kenter("{%d},{%d},%s", key->serial, authkey->serial, op);

	ret = install_user_keyrings();
	if (ret < 0)
		goto error_alloc;

	/* allocate a new session keyring */
	sprintf(desc, "_req.%u", key->serial);

	cred = get_current_cred();
	keyring = keyring_alloc(desc, cred->fsuid, cred->fsgid, cred,
				KEY_ALLOC_QUOTA_OVERRUN, NULL);
	put_cred(cred);
	if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto error_alloc;
	}

	/* attach the auth key to the session keyring */
	ret = key_link(keyring, authkey);
	if (ret < 0)
		goto error_link;

	/* record the UID and GID */
	sprintf(uid_str, "%d", cred->fsuid);
	sprintf(gid_str, "%d", cred->fsgid);

	/* we say which key is under construction */
	sprintf(key_str, "%d", key->serial);

	/* we specify the process's default keyrings */
	sprintf(keyring_str[0], "%d",
		cred->thread_keyring ? cred->thread_keyring->serial : 0);

	prkey = 0;
	if (cred->tgcred->process_keyring)
		prkey = cred->tgcred->process_keyring->serial;
	sprintf(keyring_str[1], "%d", prkey);

	rcu_read_lock();
	session = rcu_dereference(cred->tgcred->session_keyring);
	if (!session)
		session = cred->user->session_keyring;
	sskey = session->serial;
	rcu_read_unlock();

	sprintf(keyring_str[2], "%d", sskey);

	/* set up a minimal environment */
	i = 0;
	envp[i++] = "HOME=/";
	envp[i++] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[i] = NULL;

	/* set up the argument list */
	i = 0;
	argv[i++] = "/sbin/request-key";
	argv[i++] = (char *) op;
	argv[i++] = key_str;
	argv[i++] = uid_str;
	argv[i++] = gid_str;
	argv[i++] = keyring_str[0];
	argv[i++] = keyring_str[1];
	argv[i++] = keyring_str[2];
	argv[i] = NULL;

	/* do it */
	ret = call_usermodehelper_keys(argv[0], argv, envp, keyring,
				       UMH_WAIT_PROC);
	kdebug("usermode -> 0x%x", ret);
	if (ret >= 0) {
		/* ret is the exit/wait code */
		if (test_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags) ||
		    key_validate(key) < 0)
			ret = -ENOKEY;
		else
			/* ignore any errors from userspace if the key was
			 * instantiated */
			ret = 0;
	}

error_link:
	key_put(keyring);

error_alloc:
	complete_request_key(cons, ret);
	kleave(" = %d", ret);
	return ret;
}