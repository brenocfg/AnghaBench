#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * Response; int /*<<< orphan*/ * Request; int /*<<< orphan*/  CompleteEvent; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ FARM_TASK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PACK *SiFarmServWaitTask(FARM_TASK *t)
{
	PACK *response;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Wait(t->CompleteEvent, INFINITE);
	ReleaseEvent(t->CompleteEvent);
	FreePack(t->Request);

	response = t->Response;
	Free(t);

	if (PackGetInt(response, "succeed") == 0)
	{
		// Task calling fails for any reason
		FreePack(response);
		return NULL;
	}

	return response;
}