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
struct lock_class {int /*<<< orphan*/ * key; int /*<<< orphan*/  lock_entry; int /*<<< orphan*/  hash_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; struct lock_class* class; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_entries ; 
 int nr_list_entries ; 

__attribute__((used)) static void zap_class(struct lock_class *class)
{
	int i;

	/*
	 * Remove all dependencies this lock is
	 * involved in:
	 */
	for (i = 0; i < nr_list_entries; i++) {
		if (list_entries[i].class == class)
			list_del_rcu(&list_entries[i].entry);
	}
	/*
	 * Unhash the class and remove it from the all_lock_classes list:
	 */
	list_del_rcu(&class->hash_entry);
	list_del_rcu(&class->lock_entry);

	class->key = NULL;
}