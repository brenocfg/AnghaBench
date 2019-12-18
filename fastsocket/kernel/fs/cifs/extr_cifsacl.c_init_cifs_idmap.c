#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct cred {int /*<<< orphan*/  jit_keyring; struct key* thread_keyring; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int /*<<< orphan*/  KEY_REQKEY_DEFL_THREAD_KEYRING ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  cFYI (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cifs_idmap_key_type ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int,int /*<<< orphan*/ ) ; 
 int key_instantiate_and_link (struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 struct cred* prepare_kernel_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int register_key_type (TYPE_1__*) ; 
 struct cred* root_cred ; 

int
init_cifs_idmap(void)
{
	struct cred *cred;
	struct key *keyring;
	int ret;

	cFYI(1, "Registering the %s key type\n", cifs_idmap_key_type.name);

	/* create an override credential set with a special thread keyring in
	 * which requests are cached
	 *
	 * this is used to prevent malicious redirections from being installed
	 * with add_key().
	 */
	cred = prepare_kernel_cred(NULL);
	if (!cred)
		return -ENOMEM;

	keyring = key_alloc(&key_type_keyring, ".cifs_idmap", 0, 0, cred,
			    (KEY_POS_ALL & ~KEY_POS_SETATTR) |
			    KEY_USR_VIEW | KEY_USR_READ,
			    KEY_ALLOC_NOT_IN_QUOTA);
	if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto failed_put_cred;
	}

	ret = key_instantiate_and_link(keyring, NULL, 0, NULL, NULL);
	if (ret < 0)
		goto failed_put_key;

	ret = register_key_type(&cifs_idmap_key_type);
	if (ret < 0)
		goto failed_put_key;

	/* instruct request_key() to use this special keyring as a cache for
	 * the results it looks up */
	cred->thread_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	root_cred = cred;

	cFYI(1, "cifs idmap keyring: %d", key_serial(keyring));
	return 0;

failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	return ret;
}