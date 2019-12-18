#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int SessionCreated; scalar_t__ SessionSlotNumber; scalar_t__ SessionId; TYPE_1__* Api; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* C_CloseSession ) (scalar_t__) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 int /*<<< orphan*/  EraseEnumSecObjectCache (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeSecInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void CloseSecSession(SECURE *sec)
{
	// Validate arguments
	if (sec == NULL)
	{
		return;
	}
	if (sec->SessionCreated == false)
	{
		return;
	}

	// Close the session
	sec->Api->C_CloseSession(sec->SessionId);

	sec->SessionCreated = false;
	sec->SessionId = 0;
	sec->SessionSlotNumber = 0;

	FreeSecInfo(sec);

	// Clear the cache
	EraseEnumSecObjectCache(sec);
}