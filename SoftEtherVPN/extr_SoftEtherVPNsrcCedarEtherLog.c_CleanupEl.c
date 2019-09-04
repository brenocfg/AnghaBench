#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Cedar; struct TYPE_6__* LicenseStatus; int /*<<< orphan*/ * LicenseSystem; int /*<<< orphan*/  Eraser; } ;
typedef  TYPE_1__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ElFreeConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  ElStopListener (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeEraser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeEth () ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 

void CleanupEl(EL *e)
{
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	// Stop Eraser 
	FreeEraser(e->Eraser);

	// Stop Listener 
	ElStopListener(e);

	// Setting release
	ElFreeConfig(e);

	// Free the license system
	if(e->LicenseSystem != NULL)
	{
	}

	// Free the license status
	if(e->LicenseStatus != NULL)
	{
		Free(e->LicenseStatus);
	}

	// Ethernet release
	FreeEth();

	ReleaseCedar(e->Cedar);

	DeleteLock(e->lock);

	Free(e);
}