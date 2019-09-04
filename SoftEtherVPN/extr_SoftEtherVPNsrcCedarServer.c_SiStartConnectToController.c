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
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  LastError; int /*<<< orphan*/ * Server; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_1__ FARM_CONTROLLER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TRYING_TO_CONNECT ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiConnectToControllerThread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

FARM_CONTROLLER *SiStartConnectToController(SERVER *s)
{
	FARM_CONTROLLER *f;
	THREAD *t;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	f = ZeroMalloc(sizeof(FARM_CONTROLLER));
	f->Server = s;
	f->LastError = ERR_TRYING_TO_CONNECT;
	f->HaltEvent = NewEvent();
	f->lock = NewLock();

	t = NewThread(SiConnectToControllerThread, f);
	WaitThreadInit(t);
	ReleaseThread(t);

	return f;
}