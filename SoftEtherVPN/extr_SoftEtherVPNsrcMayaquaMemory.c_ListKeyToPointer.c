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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ POINTER_TO_KEY (void*) ; 

void *ListKeyToPointer(LIST *o, UINT key)
{
	UINT i;
	// Validate arguments
	if (o == NULL || key == 0)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		void *p = LIST_DATA(o, i);

		if (POINTER_TO_KEY(p) == key)
		{
			return p;
		}
	}

	return NULL;
}