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
typedef  size_t UINT ;
struct TYPE_6__ {int SessionCreated; size_t NumSlot; int IsReadOnly; size_t SessionId; size_t SessionSlotNumber; int /*<<< orphan*/  Error; int /*<<< orphan*/ * SlotIdList; TYPE_1__* Api; } ;
struct TYPE_5__ {size_t (* C_OpenSession ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 int CKF_RW_SESSION ; 
 int CKF_SERIAL_SESSION ; 
 size_t CKR_OK ; 
 int /*<<< orphan*/  GetSecInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  SEC_ERROR_INVALID_SLOT_NUMBER ; 
 int /*<<< orphan*/  SEC_ERROR_OPEN_SESSION ; 
 int /*<<< orphan*/  SEC_ERROR_SESSION_EXISTS ; 
 size_t stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 size_t stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

bool OpenSecSession(SECURE *sec, UINT slot_number)
{
	UINT err = 0;
	UINT session;
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (sec->SessionCreated)
	{
		// Already been created
		sec->Error = SEC_ERROR_SESSION_EXISTS;
		return false;
	}
	if (slot_number >= sec->NumSlot)
	{
		// Slot number is invalid
		sec->Error = SEC_ERROR_INVALID_SLOT_NUMBER;
		return false;
	}

	// Create a session
	if ((err = sec->Api->C_OpenSession(sec->SlotIdList[slot_number],
		CKF_RW_SESSION | CKF_SERIAL_SESSION, NULL, NULL, &session)) != CKR_OK)
	{
		// Failed to initialize session in read / write mode
		// Read-only mode?
		if ((err = sec->Api->C_OpenSession(sec->SlotIdList[slot_number],
			CKF_SERIAL_SESSION, NULL, NULL, &session)) != CKR_OK)
		{
			// Failure to create
			sec->Error = SEC_ERROR_OPEN_SESSION;
			return false;
		}
		else
		{
			sec->IsReadOnly = true;
		}
	}

	sec->SessionCreated = true;
	sec->SessionId = session;
	sec->SessionSlotNumber = slot_number;

	// Get the token information
	GetSecInfo(sec);

	return true;
}