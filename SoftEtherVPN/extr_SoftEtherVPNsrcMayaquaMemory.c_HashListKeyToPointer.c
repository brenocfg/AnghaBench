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
typedef  int /*<<< orphan*/  HASH_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Free (void**) ; 
 void** HashListToArray (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ POINTER_TO_KEY (void*) ; 

void *HashListKeyToPointer(HASH_LIST *h, UINT key)
{
	UINT num, i;
	void **pp;
	void *ret = NULL;
	// Validate arguments
	if (h == NULL || key == 0)
	{
		return NULL;
	}

	pp = HashListToArray(h, &num);
	if (pp == NULL)
	{
		return NULL;
	}

	for (i = 0;i < num;i++)
	{
		void *p = pp[i];

		if (POINTER_TO_KEY(p) == key)
		{
			ret = p;
		}
	}

	Free(pp);

	return ret;
}