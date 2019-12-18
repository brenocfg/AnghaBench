#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int SessionCreated; int LoginFlag; int /*<<< orphan*/  SessionId; TYPE_1__* Api; int /*<<< orphan*/  Error; scalar_t__ IsReadOnly; } ;
struct TYPE_4__ {scalar_t__ (* C_SetPIN ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  SEC_ERROR_NOT_LOGIN ; 
 int /*<<< orphan*/  SEC_ERROR_NO_SESSION ; 
 int /*<<< orphan*/  SEC_ERROR_OPEN_SESSION ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool ChangePin(SECURE *sec, char *old_pin, char *new_pin)
{
	// Validate arguments
	if (sec == NULL || old_pin == NULL || new_pin == NULL)
	{
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return false;
	}
	if (sec->LoginFlag == false)
	{
		sec->Error = SEC_ERROR_NOT_LOGIN;
		return false;
	}
	if (sec->IsReadOnly)
	{
		sec->Error = SEC_ERROR_OPEN_SESSION;
		return false;
	}

	// Change then PIN
	if (sec->Api->C_SetPIN(sec->SessionId, old_pin, StrLen(old_pin),
		new_pin, StrLen(new_pin)) != CKR_OK)
	{
		return false;
	}

	return true;
}