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
typedef  int UINT ;

/* Variables and functions */
 int UnixGetNumberOfCpuInner () ; 
 int Win32GetNumberOfCpuInner () ; 
 int cached_number_of_cpus ; 

UINT GetNumberOfCpu()
{
	UINT ret = 0;

	if (cached_number_of_cpus == 0)
	{
		UINT i = 0;

#ifdef	OS_WIN32
		i = Win32GetNumberOfCpuInner();
#else	// OS_WIN32
		i = UnixGetNumberOfCpuInner();
#endif	// OS_WIN32

		if (i == 0)
		{
			i = 8;
		}

		cached_number_of_cpus = i;
	}

	ret = cached_number_of_cpus;

	if (ret == 0)
	{
		ret = 1;
	}
	if (ret > 128)
	{
		ret = 128;
	}

	return ret;
}