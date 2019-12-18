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
struct TYPE_3__ {struct csr1212_dentry* dentries_head; } ;
struct TYPE_4__ {TYPE_1__ directory; } ;
struct csr1212_keyval {TYPE_2__ value; } ;
struct csr1212_dentry {struct csr1212_keyval* kv; struct csr1212_dentry* next; } ;

/* Variables and functions */

__attribute__((used)) static struct csr1212_dentry *
csr1212_find_keyval(struct csr1212_keyval *dir, struct csr1212_keyval *kv)
{
	struct csr1212_dentry *pos;

	for (pos = dir->value.directory.dentries_head;
	     pos != NULL; pos = pos->next)
		if (pos->kv == kv)
			return pos;
	return NULL;
}