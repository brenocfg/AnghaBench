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
struct request_key_auth {struct cred* cred; } ;
struct key_type {int dummy; } ;
struct cred {TYPE_2__* request_key_auth; } ;
typedef  scalar_t__ key_ref_t ;
typedef  int /*<<< orphan*/  key_match_func_t ;
struct TYPE_3__ {struct request_key_auth* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sem; TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOKEY ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 struct cred const* current_cred () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct key_type key_type_request_key_auth ; 
 scalar_t__ key_validate (TYPE_2__*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ search_my_process_keyrings (struct key_type*,void const*,int /*<<< orphan*/ ,int,struct cred const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

key_ref_t search_process_keyrings(struct key_type *type,
				  const void *description,
				  key_match_func_t match,
				  const struct cred *cred)
{
	struct request_key_auth *rka;
	key_ref_t key_ref, ret = ERR_PTR(-EACCES), err;

	might_sleep();

	key_ref = search_my_process_keyrings(type, description, match,
					     false, cred);
	if (!IS_ERR(key_ref))
		goto found;
	err = key_ref;

	/* if this process has an instantiation authorisation key, then we also
	 * search the keyrings of the process mentioned there
	 * - we don't permit access to request_key auth keys via this method
	 */
	if (cred->request_key_auth &&
	    cred == current_cred() &&
	    type != &key_type_request_key_auth
	    ) {
		/* defend against the auth key being revoked */
		down_read(&cred->request_key_auth->sem);

		if (key_validate(cred->request_key_auth) == 0) {
			rka = cred->request_key_auth->payload.data;

			key_ref = search_process_keyrings(type, description,
							  match, rka->cred);

			up_read(&cred->request_key_auth->sem);

			if (!IS_ERR(key_ref))
				goto found;

			ret = key_ref;
		} else {
			up_read(&cred->request_key_auth->sem);
		}
	}

	/* no key - decide on the error we're going to go for */
	if (err == ERR_PTR(-ENOKEY) || ret == ERR_PTR(-ENOKEY))
		key_ref = ERR_PTR(-ENOKEY);
	else if (err == ERR_PTR(-EACCES))
		key_ref = ret;
	else
		key_ref = err;

found:
	return key_ref;
}