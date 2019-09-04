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
typedef  void node ;

/* Variables and functions */
 void* insert (void*,void const*,int (*) (void const*,void const*),void**) ; 

void *tsearch(const void *key, void **rootp,
	int (*compar)(const void *, const void *))
{
	struct node *update;
	struct node *ret;
	if (!rootp)
		return 0;
	update = insert(*rootp, key, compar, &ret);
	if (update)
		*rootp = update;
	return ret;
}