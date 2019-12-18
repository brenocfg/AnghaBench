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
struct csr1212_keyval {TYPE_3__ value; TYPE_1__ key; } ;
struct csr1212_dentry {struct csr1212_dentry* prev; struct csr1212_dentry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_dentry*) ; 
 scalar_t__ CSR1212_KV_TYPE_DIRECTORY ; 
 struct csr1212_dentry* csr1212_find_keyval (struct csr1212_keyval*,struct csr1212_keyval*) ; 
 int /*<<< orphan*/  csr1212_release_keyval (struct csr1212_keyval*) ; 

void csr1212_detach_keyval_from_directory(struct csr1212_keyval *dir,
					  struct csr1212_keyval *kv)
{
	struct csr1212_dentry *dentry;

	if (!kv || !dir || dir->key.type != CSR1212_KV_TYPE_DIRECTORY)
		return;

	dentry = csr1212_find_keyval(dir, kv);

	if (!dentry)
		return;

	if (dentry->prev)
		dentry->prev->next = dentry->next;
	if (dentry->next)
		dentry->next->prev = dentry->prev;
	if (dir->value.directory.dentries_head == dentry)
		dir->value.directory.dentries_head = dentry->next;
	if (dir->value.directory.dentries_tail == dentry)
		dir->value.directory.dentries_tail = dentry->prev;

	CSR1212_FREE(dentry);

	csr1212_release_keyval(kv);
}