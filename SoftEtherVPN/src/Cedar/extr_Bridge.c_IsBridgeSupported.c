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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  OsType; } ;

/* Variables and functions */
 TYPE_1__* GetOsInfo () ; 
 int IsEthSupported () ; 
 int MsIsAdmin () ; 
 scalar_t__ OS_IS_WINDOWS (int /*<<< orphan*/ ) ; 

bool IsBridgeSupported()
{
	UINT type = GetOsInfo()->OsType;

	if (OS_IS_WINDOWS(type))
	{
		if (IsEthSupported())
		{
			return true;
		}
		else
		{
			bool ret = false;

#ifdef	OS_WIN32
			ret = MsIsAdmin();
#endif	// OS_WIN32

			return ret;
		}
	}
	else
	{
		return IsEthSupported();
	}
}