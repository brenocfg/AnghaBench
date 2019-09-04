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
 void* remove (void**,void const*,int (*) (void const*,void const*),void*) ; 

void *tdelete(const void *restrict key, void **restrict rootp,
	int(*compar)(const void *, const void *))
{
	if (!rootp)
		return 0;
	struct node *n = *rootp;
	struct node *ret;
	/* last argument is arbitrary non-null pointer
	   which is returned when the root node is deleted */
	ret = remove(&n, key, compar, n);
	*rootp = n;
	return ret;
}