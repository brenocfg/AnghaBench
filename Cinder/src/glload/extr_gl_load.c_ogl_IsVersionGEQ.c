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
 int g_majorVersion ; 
 int g_minorVersion ; 

int ogl_IsVersionGEQ( int testMajorVersion, int testMinorVersion )
{
	if(g_majorVersion > testMajorVersion) return 1;
	if(g_majorVersion < testMajorVersion) return 0;
	if(g_minorVersion >= testMinorVersion) return 1;
	return 0;
}