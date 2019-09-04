#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */

void CiPulseRecvThread(THREAD *thread, void *param)
{
#ifdef	OS_WIN32
	CLIENT *c = (CLIENT *)param;

	if (c == NULL)
	{
		return;
	}

	while (true)
	{
		if (c->HaltPulseThread)
		{
			break;
		}

		MsWaitForGlobalPulse(c->GlobalPulse, INFINITE);

		if (c->HaltPulseThread)
		{
			break;
		}

		CiNotifyInternal(c);
	}
#endif	// OS_WIN32
}