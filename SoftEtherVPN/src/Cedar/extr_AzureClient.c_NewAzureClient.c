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
struct TYPE_5__ {int IsEnabled; int /*<<< orphan*/  MainThread; int /*<<< orphan*/  Event; int /*<<< orphan*/  Lock; int /*<<< orphan*/ * Server; int /*<<< orphan*/ * Cedar; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_1__ AZURE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AcMainThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

AZURE_CLIENT *NewAzureClient(CEDAR *cedar, SERVER *server)
{
	AZURE_CLIENT *ac;
	// Validate arguments
	if (cedar == NULL || server == NULL)
	{
		return NULL;
	}

	ac = ZeroMalloc(sizeof(AZURE_CLIENT));

	ac->Cedar = cedar;

	ac->Server = server;

	ac->Lock = NewLock();

	ac->IsEnabled = false;

	ac->Event = NewEvent();

	// Start main thread
	ac->MainThread = NewThread(AcMainThread, ac);

	return ac;
}