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
struct keyring_list {int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_clear_rcu_disposal ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct keyring_list* rcu_dereference_locked_keyring (struct key*) ; 

__attribute__((used)) static void keyring_revoke(struct key *keyring)
{
	struct keyring_list *klist;

	klist = rcu_dereference_locked_keyring(keyring);

	/* adjust the quota */
	key_payload_reserve(keyring, 0);

	if (klist) {
		rcu_assign_pointer(keyring->payload.subscriptions, NULL);
		call_rcu(&klist->rcu, keyring_clear_rcu_disposal);
	}
}