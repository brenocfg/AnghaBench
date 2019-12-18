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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyToArray (int /*<<< orphan*/ *,void*) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 void* Malloc (int) ; 
 void* MallocFast (int) ; 

void *ToArrayEx(LIST *o, bool fast)
{
	void *p;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	// Memory allocation
	if (fast == false)
	{
		p = Malloc(sizeof(void *) * LIST_NUM(o));
	}
	else
	{
		p = MallocFast(sizeof(void *) * LIST_NUM(o));
	}
	// Copy
	CopyToArray(o, p);

	return p;
}