#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Halt; int /*<<< orphan*/  SaverHalter; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_SAVER_INTERVAL ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_1__*) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CiSaverThread(THREAD *t, void *param)
{
	CLIENT *c = (CLIENT *)param;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	NoticeThreadInit(t);

	// Wait for a certain period of time
	while (c->Halt == false)
	{
		Wait(c->SaverHalter, CLIENT_SAVER_INTERVAL);

		// Save
		CiSaveConfigurationFile(c);
	}
}