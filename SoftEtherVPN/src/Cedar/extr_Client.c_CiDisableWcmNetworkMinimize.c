#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ NoChangeWcmNetworkSettingOnWindows8; } ;
struct TYPE_5__ {TYPE_1__ Config; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  MsDisableWcmNetworkMinimize () ; 

void CiDisableWcmNetworkMinimize(CLIENT *c)
{
#ifdef	OS_WIN32
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	if (c->Config.NoChangeWcmNetworkSettingOnWindows8)
	{
		return;
	}

	MsDisableWcmNetworkMinimize();
#endif	// OS_WIN32
}