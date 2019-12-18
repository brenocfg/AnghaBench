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
struct entry {struct entry* next; int /*<<< orphan*/  comm; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 struct entry* alloc_entry () ; 
 scalar_t__ match_entries (struct entry*,struct entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_lock ; 
 struct entry** tstat_hashentry (struct entry*) ; 

__attribute__((used)) static struct entry *tstat_lookup(struct entry *entry, char *comm)
{
	struct entry **head, *curr, *prev;

	head = tstat_hashentry(entry);
	curr = *head;

	/*
	 * The fastpath is when the entry is already hashed,
	 * we do this with the lookup lock held, but with the
	 * table lock not held:
	 */
	while (curr) {
		if (match_entries(curr, entry))
			return curr;

		curr = curr->next;
	}
	/*
	 * Slowpath: allocate, set up and link a new hash entry:
	 */
	prev = NULL;
	curr = *head;

	spin_lock(&table_lock);
	/*
	 * Make sure we have not raced with another CPU:
	 */
	while (curr) {
		if (match_entries(curr, entry))
			goto out_unlock;

		prev = curr;
		curr = curr->next;
	}

	curr = alloc_entry();
	if (curr) {
		*curr = *entry;
		curr->count = 0;
		curr->next = NULL;
		memcpy(curr->comm, comm, TASK_COMM_LEN);

		smp_mb(); /* Ensure that curr is initialized before insert */

		if (prev)
			prev->next = curr;
		else
			*head = curr;
	}
 out_unlock:
	spin_unlock(&table_lock);

	return curr;
}