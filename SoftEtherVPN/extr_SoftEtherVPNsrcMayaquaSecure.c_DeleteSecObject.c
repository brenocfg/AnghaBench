#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int SessionCreated; int LoginFlag; int /*<<< orphan*/  Error; int /*<<< orphan*/  SessionId; TYPE_1__* Api; } ;
struct TYPE_8__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Name; int /*<<< orphan*/  Object; scalar_t__ Private; } ;
struct TYPE_7__ {scalar_t__ (* C_DestroyObject ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SEC_OBJ ;
typedef  TYPE_3__ SECURE ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  DeleteSecObjFromEnumCache (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PARAMETER ; 
 int /*<<< orphan*/  SEC_ERROR_HARDWARE_ERROR ; 
 int /*<<< orphan*/  SEC_ERROR_NOT_LOGIN ; 
 int /*<<< orphan*/  SEC_ERROR_NO_SESSION ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool DeleteSecObject(SECURE *sec, SEC_OBJ *obj)
{
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (obj == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return false;
	}
	if (sec->LoginFlag == false && obj->Private)
	{
		sec->Error = SEC_ERROR_NOT_LOGIN;
		return false;
	}

	// Delete the Object
	if (sec->Api->C_DestroyObject(sec->SessionId, obj->Object) != CKR_OK)
	{
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		return false;
	}

	// Clear the Cache
	DeleteSecObjFromEnumCache(sec, obj->Name, obj->Type);

	return true;
}