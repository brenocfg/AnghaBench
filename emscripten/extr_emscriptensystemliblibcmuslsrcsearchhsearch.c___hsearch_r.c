#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hsearch_data {TYPE_1__* __tab; } ;
struct TYPE_7__ {scalar_t__ key; } ;
struct TYPE_6__ {int used; int mask; } ;
typedef  TYPE_2__ ENTRY ;
typedef  scalar_t__ ACTION ;

/* Variables and functions */
 scalar_t__ FIND ; 
 size_t keyhash (scalar_t__) ; 
 TYPE_2__* lookup (scalar_t__,size_t,struct hsearch_data*) ; 
 int /*<<< orphan*/  resize (int,struct hsearch_data*) ; 

int __hsearch_r(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab)
{
	size_t hash = keyhash(item.key);
	ENTRY *e = lookup(item.key, hash, htab);

	if (e->key) {
		*retval = e;
		return 1;
	}
	if (action == FIND) {
		*retval = 0;
		return 0;
	}
	*e = item;
	if (++htab->__tab->used > htab->__tab->mask - htab->__tab->mask/4) {
		if (!resize(2*htab->__tab->used, htab)) {
			htab->__tab->used--;
			e->key = 0;
			*retval = 0;
			return 0;
		}
		e = lookup(item.key, hash, htab);
	}
	*retval = e;
	return 1;
}