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
struct TYPE_3__ {int Halt; int NoMoreSave; int /*<<< orphan*/  AutoSaveConfigSpan; int /*<<< orphan*/  SaveHaltEvent; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  SiWriteConfigurationFile (TYPE_1__*) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiSaverThread(THREAD *thread, void *param)
{
	SERVER *s = (SERVER *)param;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	while (s->Halt == false)
	{
		// Save to the configuration file
		if (s->NoMoreSave == false)
		{
			SiWriteConfigurationFile(s);
		}

		Wait(s->SaveHaltEvent, s->AutoSaveConfigSpan);
	}
}