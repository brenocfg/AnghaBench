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
typedef  int /*<<< orphan*/  SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 

UINT SiDebugProcDump(SERVER *s, char *in_str, char *ret_str, UINT ret_str_size)
{
	// Validate arguments
	if (s == NULL || in_str == NULL || ret_str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

#ifdef	OS_WIN32
	MsWriteMinidump(NULL, NULL);
#else	// OS_WIN32
	return ERR_NOT_SUPPORTED;
#endif	// OS_WIN32

	return ERR_NO_ERROR;
}