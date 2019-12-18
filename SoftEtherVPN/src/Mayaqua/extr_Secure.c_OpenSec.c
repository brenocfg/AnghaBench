#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int IsEPass1000; int NumSlot; scalar_t__* SlotIdList; TYPE_1__* Api; TYPE_2__* Dev; int /*<<< orphan*/  Error; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  DeviceName; } ;
struct TYPE_10__ {scalar_t__ (* C_GetSlotList ) (int,scalar_t__*,int*) ;} ;
typedef  TYPE_2__ SECURE_DEVICE ;
typedef  TYPE_3__ SECURE ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  CloseSec (TYPE_3__*) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  FreeSecModule (TYPE_3__*) ; 
 TYPE_2__* GetSecureDevice (scalar_t__) ; 
 scalar_t__ INFINITE ; 
 int LoadSecModule (TYPE_3__*) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  SEC_ERROR_NOERROR ; 
 scalar_t__ SearchStrEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 TYPE_3__* ZeroMalloc (int) ; 
 scalar_t__ stub1 (int,scalar_t__*,int*) ; 
 scalar_t__ stub2 (int,scalar_t__*,int*) ; 

SECURE *OpenSec(UINT id)
{
	SECURE_DEVICE *dev = GetSecureDevice(id);
	SECURE *sec;
	UINT err;

	if (dev == NULL)
	{
		return NULL;
	}

	sec = ZeroMalloc(sizeof(SECURE));

	sec->lock = NewLock();
	sec->Error = SEC_ERROR_NOERROR;
	sec->Dev = dev;

	// Get whether it's a ePass or not
	if (SearchStrEx(dev->DeviceName, "epass", 0, false) != INFINITE)
	{
		sec->IsEPass1000 = true;
	}

	// Load the module
	if (LoadSecModule(sec) == false)
	{
		CloseSec(sec);
		return NULL;
	}

	// Get the slot list
	sec->NumSlot = 0;
	if ((err = sec->Api->C_GetSlotList(true, NULL, &sec->NumSlot)) != CKR_OK || sec->NumSlot == 0)
	{
		// Failure
		FreeSecModule(sec);
		CloseSec(sec);
		return NULL;
	}

	sec->SlotIdList = (UINT *)ZeroMalloc(sizeof(UINT) * sec->NumSlot);

	if (sec->Api->C_GetSlotList(TRUE, sec->SlotIdList, &sec->NumSlot) != CKR_OK)
	{
		// Failure
		Free(sec->SlotIdList);
		sec->SlotIdList = NULL;
		FreeSecModule(sec);
		CloseSec(sec);
		return NULL;
	}

	return sec;
}