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
struct pmb_entry {struct pmb_entry* next; } ;

/* Variables and functions */
 struct pmb_entry* pmb_list ; 

__attribute__((used)) static inline void pmb_list_del(struct pmb_entry *pmbe)
{
	struct pmb_entry **p, *tmp;

	for (p = &pmb_list; (tmp = *p); p = &tmp->next)
		if (tmp == pmbe) {
			*p = tmp->next;
			return;
		}
}