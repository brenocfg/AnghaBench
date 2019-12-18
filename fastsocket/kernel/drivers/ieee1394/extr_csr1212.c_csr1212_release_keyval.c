#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct csr1212_dentry* dentries_tail; struct csr1212_dentry* dentries_head; } ;
struct TYPE_6__ {TYPE_2__ directory; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct csr1212_keyval {TYPE_3__ value; TYPE_1__ key; struct csr1212_keyval* associate; int /*<<< orphan*/  refcnt; } ;
struct csr1212_dentry {struct csr1212_dentry* prev; struct csr1212_dentry* next; struct csr1212_keyval* kv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_dentry*) ; 
 scalar_t__ CSR1212_KV_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_keyval (struct csr1212_keyval*) ; 

void csr1212_release_keyval(struct csr1212_keyval *kv)
{
	struct csr1212_keyval *k, *a;
	struct csr1212_dentry dentry;
	struct csr1212_dentry *head, *tail;

	if (!atomic_dec_and_test(&kv->refcnt))
		return;

	dentry.kv = kv;
	dentry.next = NULL;
	dentry.prev = NULL;

	head = &dentry;
	tail = head;

	while (head) {
		k = head->kv;

		while (k) {
			/* must not dec_and_test kv->refcnt again */
			if (k != kv && !atomic_dec_and_test(&k->refcnt))
				break;

			a = k->associate;

			if (k->key.type == CSR1212_KV_TYPE_DIRECTORY) {
				/* If the current entry is a directory, move all
				 * the entries to the destruction list. */
				if (k->value.directory.dentries_head) {
					tail->next =
					    k->value.directory.dentries_head;
					k->value.directory.dentries_head->prev =
					    tail;
					tail = k->value.directory.dentries_tail;
				}
			}
			free_keyval(k);
			k = a;
		}

		head = head->next;
		if (head) {
			if (head->prev && head->prev != &dentry)
				CSR1212_FREE(head->prev);
			head->prev = NULL;
		} else if (tail != &dentry) {
			CSR1212_FREE(tail);
		}
	}
}