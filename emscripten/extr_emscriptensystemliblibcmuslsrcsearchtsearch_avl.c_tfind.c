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

/* Variables and functions */
 void* find (void* const,void const*,int (*) (void const*,void const*)) ; 

void *tfind(const void *key, void *const *rootp,
	int(*compar)(const void *, const void *))
{
	if (!rootp)
		return 0;
	return find(*rootp, key, compar);
}