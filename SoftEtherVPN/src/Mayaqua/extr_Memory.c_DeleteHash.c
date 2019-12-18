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
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * AllList; int /*<<< orphan*/ ** Entries; int /*<<< orphan*/  NumItems; } ;
typedef  TYPE_1__ HASH_LIST ;

/* Variables and functions */
 size_t CalcHashForHashList (TYPE_1__*,void*) ; 
 scalar_t__ Delete (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

bool DeleteHash(HASH_LIST *h, void *p)
{
	UINT r;
	bool ret = false;
	// Validate arguments
	if (h == NULL || p == NULL)
	{
		return false;
	}

	r = CalcHashForHashList(h, p);

	if (h->Entries[r] != NULL)
	{
		if (Delete(h->Entries[r], p))
		{
			ret = true;
			h->NumItems--;
		}

		if (LIST_NUM(h->Entries[r]) == 0)
		{
			ReleaseList(h->Entries[r]);
			h->Entries[r] = NULL;
		}
	}

	if (ret)
	{
		if (h->AllList != NULL)
		{
			Delete(h->AllList, p);
		}
	}

	return ret;
}