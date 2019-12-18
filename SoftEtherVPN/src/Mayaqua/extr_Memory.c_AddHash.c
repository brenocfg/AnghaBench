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
struct TYPE_4__ {int /*<<< orphan*/  NumItems; int /*<<< orphan*/ * AllList; int /*<<< orphan*/ ** Entries; int /*<<< orphan*/  CompareProc; } ;
typedef  TYPE_1__ HASH_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,void*) ; 
 size_t CalcHashForHashList (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ ) ; 

void AddHash(HASH_LIST *h, void *p)
{
	UINT r;
	// Validate arguments
	if (h == NULL || p == NULL)
	{
		return;
	}

	r = CalcHashForHashList(h, p);

	if (h->Entries[r] == NULL)
	{
		h->Entries[r] = NewListFast(h->CompareProc);
	}

	Insert(h->Entries[r], p);

	if (h->AllList != NULL)
	{
		Add(h->AllList, p);
	}

	h->NumItems++;
}