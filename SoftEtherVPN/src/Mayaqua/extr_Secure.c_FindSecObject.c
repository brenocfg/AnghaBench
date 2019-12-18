#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int SessionCreated; int /*<<< orphan*/  Error; } ;
struct TYPE_9__ {scalar_t__ Type; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ SEC_OBJ ;
typedef  TYPE_2__ SECURE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* CloneSecObject (TYPE_1__*) ; 
 int /*<<< orphan*/ * EnumSecObject (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeEnumSecObject (int /*<<< orphan*/ *) ; 
 scalar_t__ INFINITE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PARAMETER ; 
 int /*<<< orphan*/  SEC_ERROR_NO_SESSION ; 
 int /*<<< orphan*/  SEC_ERROR_OBJ_NOT_FOUND ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 

SEC_OBJ *FindSecObject(SECURE *sec, char *name, UINT type)
{
	LIST *o;
	UINT i;
	SEC_OBJ *ret = NULL;
	// Validate arguments
	if (sec == NULL)
	{
		return NULL;
	}
	if (name == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return NULL;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return 0;
	}

	// Enumeration
	o = EnumSecObject(sec);
	if (o == NULL)
	{
		return NULL;
	}
	for (i = 0;i < LIST_NUM(o);i++)
	{
		SEC_OBJ *obj = LIST_DATA(o, i);

		if (obj->Type == type || type == INFINITE)
		{
			if (StrCmpi(obj->Name, name) == 0)
			{
				ret = CloneSecObject(obj);
				break;
			}
		}
	}
	FreeEnumSecObject(o);

	if (ret == NULL)
	{
		sec->Error = SEC_ERROR_OBJ_NOT_FOUND;
	}

	return ret;
}