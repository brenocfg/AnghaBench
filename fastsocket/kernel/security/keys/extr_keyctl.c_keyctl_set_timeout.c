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
typedef  unsigned int time_t ;
struct timespec {unsigned int tv_sec; } ;
struct key {unsigned int expiry; int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  struct key* key_ref_t ;

/* Variables and functions */
 long EACCES ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_LOOKUP_CREATE ; 
 int KEY_LOOKUP_PARTIAL ; 
 int /*<<< orphan*/  KEY_SETATTR ; 
 long PTR_ERR (struct key*) ; 
 struct timespec current_kernel_time () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned int key_gc_delay ; 
 struct key* key_get_instantiation_authkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (struct key*) ; 
 int /*<<< orphan*/  key_schedule_gc (unsigned int) ; 
 struct key* lookup_user_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

long keyctl_set_timeout(key_serial_t id, unsigned timeout)
{
	struct timespec now;
	struct key *key, *instkey;
	key_ref_t key_ref;
	time_t expiry;
	long ret;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_SETATTR);
	if (IS_ERR(key_ref)) {
		/* setting the timeout on a key under construction is permitted
		 * if we have the authorisation token handy */
		if (PTR_ERR(key_ref) == -EACCES) {
			instkey = key_get_instantiation_authkey(id);
			if (!IS_ERR(instkey)) {
				key_put(instkey);
				key_ref = lookup_user_key(id,
							  KEY_LOOKUP_PARTIAL,
							  0);
				if (!IS_ERR(key_ref))
					goto okay;
			}
		}

		ret = PTR_ERR(key_ref);
		goto error;
	}

okay:
	key = key_ref_to_ptr(key_ref);

	/* make the changes with the locks held to prevent races */
	down_write(&key->sem);

	expiry = 0;
	if (timeout > 0) {
		now = current_kernel_time();
		expiry = now.tv_sec + timeout;
	}

	key->expiry = expiry;
	key_schedule_gc(key->expiry + key_gc_delay);

	up_write(&key->sem);
	key_put(key);

	ret = 0;
error:
	return ret;
}