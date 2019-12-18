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
struct keyring_list {int nkeys; struct key** keys; } ;
struct key_type {scalar_t__ (* match ) (struct key*,char const*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {int /*<<< orphan*/  usage; int /*<<< orphan*/  flags; struct key_type const* type; TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  key_ref_t ;
typedef  int /*<<< orphan*/  key_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned long is_key_possessed (int /*<<< orphan*/ ) ; 
 scalar_t__ key_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_key_ref (struct key*,unsigned long) ; 
 struct keyring_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ stub1 (struct key*,char const*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

key_ref_t __keyring_search_one(key_ref_t keyring_ref,
			       const struct key_type *ktype,
			       const char *description,
			       key_perm_t perm)
{
	struct keyring_list *klist;
	unsigned long possessed;
	struct key *keyring, *key;
	int nkeys, loop;

	keyring = key_ref_to_ptr(keyring_ref);
	possessed = is_key_possessed(keyring_ref);

	rcu_read_lock();

	klist = rcu_dereference(keyring->payload.subscriptions);
	if (klist) {
		nkeys = klist->nkeys;
		smp_rmb();
		for (loop = 0; loop < nkeys ; loop++) {
			key = klist->keys[loop];

			if (key->type == ktype &&
			    (!key->type->match ||
			     key->type->match(key, description)) &&
			    key_permission(make_key_ref(key, possessed),
					   perm) == 0 &&
			    !test_bit(KEY_FLAG_REVOKED, &key->flags)
			    )
				goto found;
		}
	}

	rcu_read_unlock();
	return ERR_PTR(-ENOKEY);

found:
	atomic_inc(&key->usage);
	rcu_read_unlock();
	return make_key_ref(key, possessed);
}