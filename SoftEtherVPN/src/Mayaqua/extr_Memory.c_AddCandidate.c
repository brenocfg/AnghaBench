#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* Str; void* LastSelectedTime; } ;
typedef  TYPE_1__ wchar_t ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CANDIDATE ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 void* SystemTime64 () ; 
 void* UniCopyStr (TYPE_1__*) ; 
 scalar_t__ UniStrCmpi (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  UniTrim (TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void AddCandidate(LIST *o, wchar_t *str, UINT num_max)
{
	UINT i;
	bool exists;
	// Validate arguments
	if (o == NULL || str == NULL)
	{
		return;
	}
	if (num_max == 0)
	{
		num_max = 0x7fffffff;
	}

	// String copy
	str = UniCopyStr(str);
	UniTrim(str);

	exists = false;
	for (i = 0;i < LIST_NUM(o);i++)
	{
		CANDIDATE *c = LIST_DATA(o, i);
		if (UniStrCmpi(c->Str, str) == 0)
		{
			// Update the time that an existing entry have been found
			c->LastSelectedTime = SystemTime64();
			exists = true;
			break;
		}
	}

	if (exists == false)
	{
		// Insert new
		CANDIDATE *c = ZeroMalloc(sizeof(CANDIDATE));
		c->LastSelectedTime = SystemTime64();
		c->Str = UniCopyStr(str);
		Insert(o, c);
	}

	// Release the string
	Free(str);

	// Check the current number of candidates.
	// If it is more than num_max, remove from an oldest candidate sequentially.
	if (LIST_NUM(o) > num_max)
	{
		while (LIST_NUM(o) > num_max)
		{
			UINT index = LIST_NUM(o) - 1;
			CANDIDATE *c = LIST_DATA(o, index);
			Delete(o, c);
			Free(c->Str);
			Free(c);
		}
	}
}