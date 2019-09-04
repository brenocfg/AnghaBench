#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Sock; int /*<<< orphan*/  Event; scalar_t__ HaltThread; TYPE_1__* Session; } ;
struct TYPE_3__ {scalar_t__ Halt; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ CNC_CONNECT_ERROR_DLG_THREAD_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 

void CncCheckCertHaltThread(THREAD *thread, void *param)
{
	CNC_CONNECT_ERROR_DLG_THREAD_PARAM *dp = (CNC_CONNECT_ERROR_DLG_THREAD_PARAM *)param;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	while (true)
	{
		if (dp->Session->Halt || dp->HaltThread)
		{
			break;
		}

		Wait(dp->Event, 100);
	}

	Disconnect(dp->Sock);
}