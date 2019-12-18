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
struct key {int dummy; } ;
struct cred {int /*<<< orphan*/  request_key_auth; } ;

/* Variables and functions */
 int ENOMEM ; 
 int commit_creds (struct cred*) ; 
 int /*<<< orphan*/  key_get (struct key*) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 struct cred* prepare_creds () ; 

__attribute__((used)) static int keyctl_change_reqkey_auth(struct key *key)
{
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	key_put(new->request_key_auth);
	new->request_key_auth = key_get(key);

	return commit_creds(new);
}