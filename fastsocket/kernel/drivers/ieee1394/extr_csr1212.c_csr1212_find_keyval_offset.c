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
typedef  scalar_t__ u32 ;
struct csr1212_keyval {scalar_t__ offset; struct csr1212_keyval* next; } ;

/* Variables and functions */

__attribute__((used)) static struct csr1212_keyval *
csr1212_find_keyval_offset(struct csr1212_keyval *kv_list, u32 offset)
{
	struct csr1212_keyval *kv;

	for (kv = kv_list->next; kv && (kv != kv_list); kv = kv->next)
		if (kv->offset == offset)
			return kv;
	return NULL;
}