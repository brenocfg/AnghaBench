#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct key {TYPE_1__ type_data; scalar_t__ description; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (TYPE_2__*) ; 
 int keyring_hash (scalar_t__) ; 
 TYPE_2__* keyring_name_hash ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyring_publish_name(struct key *keyring)
{
	int bucket;

	if (keyring->description) {
		bucket = keyring_hash(keyring->description);

		write_lock(&keyring_name_lock);

		if (!keyring_name_hash[bucket].next)
			INIT_LIST_HEAD(&keyring_name_hash[bucket]);

		list_add_tail(&keyring->type_data.link,
			      &keyring_name_hash[bucket]);

		write_unlock(&keyring_name_lock);
	}
}