#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int majorVersion; int minorVersion; int compatibilityProfile; int (* LoadVersion ) () ;} ;

/* Variables and functions */
 int g_numVersionMapEntries ; 
 TYPE_1__* g_versionMapTable ; 
 int stub1 () ; 

__attribute__((used)) static int LoadVersionFromMap(int major, int minor, int compatibilityProfile)
{
	int loop = 0;
	for(; loop < g_numVersionMapEntries; ++loop)
	{
		if(
			(g_versionMapTable[loop].majorVersion == major) &&
			(g_versionMapTable[loop].minorVersion == minor) &&
			(g_versionMapTable[loop].compatibilityProfile == compatibilityProfile))
		{
			return g_versionMapTable[loop].LoadVersion();
		}
	}
	
	return -1;
}