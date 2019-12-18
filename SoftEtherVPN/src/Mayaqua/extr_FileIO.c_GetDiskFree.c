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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 int UnixGetDiskFree (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Win32GetDiskFree (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool GetDiskFree(char *path, UINT64 *free_size, UINT64 *used_size, UINT64 *total_size)
{
	bool ret;
	// Validate arguments
	if (path == NULL)
	{
		path = "./";
	}

#ifdef	OS_WIN32
	ret = Win32GetDiskFree(path, free_size, used_size, total_size);
#else	// OS_WIN32
	ret = UnixGetDiskFree(path, free_size, used_size, total_size);
#endif	// OS_WIN32

	return ret;
}