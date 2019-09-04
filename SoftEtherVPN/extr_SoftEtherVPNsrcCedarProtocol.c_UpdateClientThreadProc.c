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
struct TYPE_5__ {int DisableCheck; } ;
struct TYPE_6__ {int /*<<< orphan*/  HaltEvent; TYPE_1__ Setting; scalar_t__ HaltFlag; int /*<<< orphan*/  Param; scalar_t__ (* IsForegroundCb ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ UPDATE_CLIENT ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int GenRandInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_CHECK_INTERVAL_MAX ; 
 int /*<<< orphan*/  UPDATE_CHECK_INTERVAL_MIN ; 
 int /*<<< orphan*/  UpdateClientThreadMain (TYPE_2__*) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void UpdateClientThreadProc(THREAD *thread, void *param)
{
	UPDATE_CLIENT *c = (UPDATE_CLIENT *)param;
	bool first_loop = true;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	while (true)
	{
		// Termination check
		if (c->HaltFlag)
		{
			break;
		}

		if (first_loop == false)
		{
			// Wait for the foreground
			if (c->IsForegroundCb != NULL)
			{
				while (true)
				{
					if (c->HaltFlag)
					{
						break;
					}

					if (c->IsForegroundCb(c, c->Param))
					{
						break;
					}

					Wait(c->HaltEvent, 1000);
				}
			}
		}

		first_loop = false;

		if (c->HaltFlag)
		{
			break;
		}

		if (c->Setting.DisableCheck == false)
		{
			UpdateClientThreadMain(c);
		}

		// Wait until the next attempt
		Wait(c->HaltEvent, GenRandInterval(UPDATE_CHECK_INTERVAL_MIN, UPDATE_CHECK_INTERVAL_MAX));
	}
}