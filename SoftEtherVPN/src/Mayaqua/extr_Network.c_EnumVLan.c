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
 char** UnixEnumVLan (char*) ; 
 char** Win32EnumVLan (char*) ; 

char **EnumVLan(char *tag_name)
{
	char **ret = NULL;
#ifdef	OS_WIN32
	ret = Win32EnumVLan(tag_name);
#else	// OS_WIN32
	ret = UnixEnumVLan(tag_name);
#endif	// OS_WIN32
	return ret;
}