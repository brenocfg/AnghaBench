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
typedef  int /*<<< orphan*/  SEC_OBJ ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloneSecObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 

LIST *CloneEnumSecObject(LIST *o)
{
	LIST *ret;
	UINT i;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	ret = NewListFast(NULL);
	for (i = 0;i < LIST_NUM(o);i++)
	{
		SEC_OBJ *obj = LIST_DATA(o, i);

		Add(ret, CloneSecObject(obj));
	}

	return ret;
}