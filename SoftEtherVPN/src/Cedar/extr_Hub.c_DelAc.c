#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ Id; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ AC ;

/* Variables and functions */
 scalar_t__ Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NormalizeAcList (int /*<<< orphan*/ *) ; 

bool DelAc(LIST *o, UINT id)
{
	UINT i;
	// Validate arguments
	if (o == NULL || id == 0)
	{
		return false;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		AC *ac = LIST_DATA(o, i);

		if (ac->Id == id)
		{
			if (Delete(o, ac))
			{
				Free(ac);

				NormalizeAcList(o);

				return true;
			}
		}
	}

	return false;
}