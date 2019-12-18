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
struct dev_addr_list {int da_addrlen; int da_gusers; struct dev_addr_list* next; scalar_t__ da_users; int /*<<< orphan*/  da_addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  kfree (struct dev_addr_list*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void*,int) ; 

int __dev_addr_delete(struct dev_addr_list **list, int *count,
		      void *addr, int alen, int glbl)
{
	struct dev_addr_list *da;

	for (; (da = *list) != NULL; list = &da->next) {
		if (memcmp(da->da_addr, addr, da->da_addrlen) == 0 &&
		    alen == da->da_addrlen) {
			if (glbl) {
				int old_glbl = da->da_gusers;
				da->da_gusers = 0;
				if (old_glbl == 0)
					break;
			}
			if (--da->da_users)
				return 0;

			*list = da->next;
			kfree(da);
			(*count)--;
			return 0;
		}
	}
	return -ENOENT;
}