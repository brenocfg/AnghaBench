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
 char* CLIENT_WIN32_EXE_FILENAME ; 
 char* CLIENT_WIN32_EXE_FILENAME_IA64 ; 
 char* CLIENT_WIN32_EXE_FILENAME_X64 ; 
 int Is64 () ; 
 scalar_t__ IsX64 () ; 

char *CiGetVpnClientExeFileName()
{
	if (Is64() == false)
	{
		return CLIENT_WIN32_EXE_FILENAME;
	}
	else
	{
		if (IsX64())
		{
			return CLIENT_WIN32_EXE_FILENAME_X64;
		}
		else
		{
			return CLIENT_WIN32_EXE_FILENAME_IA64;
		}
	}
}