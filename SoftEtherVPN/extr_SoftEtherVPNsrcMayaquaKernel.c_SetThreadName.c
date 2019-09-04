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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */

void SetThreadName(UINT thread_id, char *name, void *param)
{
#ifdef	OS_WIN32
	if (IsDebug())
	{
		char tmp[MAX_SIZE];

		if (name == NULL)
		{
			strcpy(tmp, "idle");
		}
		else
		{
			sprintf(tmp, "%s (0x%x)", name, (UINT)param);
		}

		Win32SetThreadName(thread_id, tmp);
	}
#else	// OS_WIN32
#ifdef	_DEBUG
#ifdef	PR_SET_NAME
	char tmp[MAX_SIZE];

	if (name == NULL)
	{
		strcpy(tmp, "idle");
	}
	else
	{
		sprintf(tmp, "%s (%p)", name, param);
	}

	tmp[15] = 0;

	prctl(PR_SET_NAME, (unsigned long)tmp, 0, 0, 0);
#endif	// PR_SET_NAME
#endif	// _DEBUG
#endif	// OS_WIN32
}