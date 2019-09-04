#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {int NumItems; size_t Size; int /*<<< orphan*/ ** Entries; int /*<<< orphan*/ * AllList; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ HASH_LIST ;

/* Variables and functions */
 void* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 void** ToArray (int /*<<< orphan*/ *) ; 
 void** ZeroMalloc (int) ; 

void **HashListToArray(HASH_LIST *h, UINT *num)
{
	void **ret = NULL;
	UINT i;
	UINT n = 0;
	// Validate arguments
	if (h == NULL || num == NULL)
	{
		if (num != NULL)
		{
			*num = 0;
		}
		return NULL;
	}

	if (h->AllList != NULL)
	{
		*num = LIST_NUM(h->AllList);

		return ToArray(h->AllList);
	}

	ret = ZeroMalloc(sizeof(void *) * h->NumItems);

	for (i = 0;i < h->Size;i++)
	{
		LIST *o = h->Entries[i];

		if (o != NULL)
		{
			UINT j;

			for (j = 0;j < LIST_NUM(o);j++)
			{
				void *p = LIST_DATA(o, j);

				ret[n] = p;
				n++;
			}
		}
	}

	*num = n;

	return ret;
}