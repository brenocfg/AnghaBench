#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct keyring_list {int nkeys; int /*<<< orphan*/ * keys; } ;
struct TYPE_5__ {int /*<<< orphan*/  subscriptions; } ;
struct TYPE_7__ {int /*<<< orphan*/ * next; } ;
struct TYPE_6__ {TYPE_3__ link; } ;
struct key {TYPE_1__ payload; TYPE_2__ type_data; scalar_t__ description; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  kfree (struct keyring_list*) ; 
 int /*<<< orphan*/  list_del (TYPE_3__*) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 struct keyring_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyring_destroy(struct key *keyring)
{
	struct keyring_list *klist;
	int loop;

	if (keyring->description) {
		write_lock(&keyring_name_lock);

		if (keyring->type_data.link.next != NULL &&
		    !list_empty(&keyring->type_data.link))
			list_del(&keyring->type_data.link);

		write_unlock(&keyring_name_lock);
	}

	klist = rcu_dereference(keyring->payload.subscriptions);
	if (klist) {
		for (loop = klist->nkeys - 1; loop >= 0; loop--)
			key_put(klist->keys[loop]);
		kfree(klist);
	}
}