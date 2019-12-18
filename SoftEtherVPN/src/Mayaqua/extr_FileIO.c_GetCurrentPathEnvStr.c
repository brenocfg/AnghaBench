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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int GetEnv (char*,char*,int) ; 
 int /*<<< orphan*/  UnixGetCurrentDir (char*,int) ; 
 int /*<<< orphan*/  Win32GetCurrentDir (char*,int) ; 

char *GetCurrentPathEnvStr()
{
	char tmp[1024];
	char *tag_name;

#ifdef	OS_WIN32
	tag_name = "Path";
#else	// OS_WIN32
	tag_name = "PATH";
#endif	// OS_WIN32

	if (GetEnv(tag_name, tmp, sizeof(tmp)) == false)
	{
#ifdef	OS_WIN32
		Win32GetCurrentDir(tmp, sizeof(tmp));
#else	// OS_WIN32
		UnixGetCurrentDir(tmp, sizeof(tmp));
#endif	// OS_WIN32
	}

	return CopyStr(tmp);
}