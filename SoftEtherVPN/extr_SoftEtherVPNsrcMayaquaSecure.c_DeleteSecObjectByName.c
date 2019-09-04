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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int SessionCreated; int /*<<< orphan*/  Error; } ;
typedef  int /*<<< orphan*/  SEC_OBJ ;
typedef  TYPE_1__ SECURE ;

/* Variables and functions */
 int DeleteSecObject (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FindSecObject (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSecObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PARAMETER ; 
 int /*<<< orphan*/  SEC_ERROR_NO_SESSION ; 

bool DeleteSecObjectByName(SECURE *sec, char *name, UINT type)
{
	bool ret;
	SEC_OBJ *obj;
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (name == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return false;
	}

	// Get the Object
	obj = FindSecObject(sec, name, type);
	if (obj == NULL)
	{
		// Failure
		return false;
	}

	// Delete the Object 
	ret = DeleteSecObject(sec, obj);

	// Memory release
	FreeSecObject(obj);

	return ret;
}