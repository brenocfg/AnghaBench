#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sorted; int /*<<< orphan*/ * cmp; int /*<<< orphan*/  num_item; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_SEARCH_COUNT ; 
 int /*<<< orphan*/  Sort (TYPE_1__*) ; 
 scalar_t__ bsearch (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int (*) (void const*,void const*)) ; 

void *Search(LIST *o, void *target)
{
	void **ret;
	// Validate arguments
	if (o == NULL || target == NULL)
	{
		return NULL;
	}
	if (o->cmp == NULL)
	{
		return NULL;
	}

	// Check the sort
	if (o->sorted == false)
	{
		// Sort because it is not sorted
		Sort(o);
	}

	ret = (void **)bsearch(&target, o->p, o->num_item, sizeof(void *),
		(int(*)(const void *, const void *))o->cmp);

	// KS
	KS_INC(KS_SEARCH_COUNT);

	if (ret != NULL)
	{
		return *ret;
	}
	else
	{
		return NULL;
	}
}