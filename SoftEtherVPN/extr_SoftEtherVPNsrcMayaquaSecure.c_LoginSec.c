#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int SessionCreated; int LoginFlag; int /*<<< orphan*/  Error; int /*<<< orphan*/  SessionId; TYPE_1__* Api; } ;
struct TYPE_5__ {scalar_t__ (* C_Login ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  CKU_USER ; 
 int /*<<< orphan*/  EraseEnumSecObjectCache (TYPE_2__*) ; 
 int /*<<< orphan*/  SEC_ERROR_ALREADY_LOGIN ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PIN_CODE ; 
 int /*<<< orphan*/  SEC_ERROR_NO_PIN_STR ; 
 int /*<<< orphan*/  SEC_ERROR_NO_SESSION ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool LoginSec(SECURE *sec, char *pin)
{
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return false;

	}
	if (sec->LoginFlag)
	{
		sec->Error = SEC_ERROR_ALREADY_LOGIN;
		return false;
	}
	if (pin == NULL)
	{
		sec->Error = SEC_ERROR_NO_PIN_STR;
		return false;
	}

	// Log-in
	if (sec->Api->C_Login(sec->SessionId, CKU_USER, pin, StrLen(pin)) != CKR_OK)
	{
		// Login failure
		sec->Error = SEC_ERROR_BAD_PIN_CODE;
		return false;
	}

	// Clear the cache
	EraseEnumSecObjectCache(sec);

	sec->LoginFlag = true;

	return true;
}