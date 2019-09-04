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

/* Variables and functions */

bool CiWriteLastMachineHash(void *data)
{
	// Validate arguments
	if (data == NULL)
	{
		return false;
	}

#ifdef OS_WIN32
	if (MsRegWriteBinEx(REG_LOCAL_MACHINE, MS_REG_TCP_SETTING_KEY, "LastMachineHash", data, SHA1_SIZE, true) == false)
	{
		return false;
	}

	return true;
#else	// OS_WIN32
	return false;
#endif	// OS_WIN32
}