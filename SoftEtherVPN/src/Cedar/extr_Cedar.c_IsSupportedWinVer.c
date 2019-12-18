#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int IsWindows; int IsNT; int VerMajor; int VerMinor; int ServicePack; scalar_t__ IsBeta; } ;
typedef  TYPE_1__ RPC_WINVER ;

/* Variables and functions */

bool IsSupportedWinVer(RPC_WINVER *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return false;
	}

	if (v->IsWindows == false)
	{
		return true;
	}

	if (v->IsNT == false)
	{
		return true;
	}

	if (v->IsBeta)
	{
		return true;
	}

	if (v->VerMajor <= 4)
	{
		// Windows NT
		return true;
	}

	if (v->VerMajor == 5 && v->VerMinor == 0)
	{
		// Windows 2000
		if (v->ServicePack <= 4)
		{
			// SP4 or earlier
			return true;
		}
	}

	if (v->VerMajor == 5 && v->VerMinor == 1)
	{
		// Windows XP x86
		if (v->ServicePack <= 3)
		{
			// SP3 or earlier
			return true;
		}
	}

	if (v->VerMajor == 5 && v->VerMinor == 2)
	{
		// Windows XP x64, Windows Server 2003
		if (v->ServicePack <= 2)
		{
			// SP2 or earlier
			return true;
		}
	}

	if (v->VerMajor == 6 && v->VerMinor == 0)
	{
		// Windows Vista, Server 2008
		if (v->ServicePack <= 2)
		{
			// SP2 or earlier
			return true;
		}
	}

	if (v->VerMajor == 6 && v->VerMinor == 1)
	{
		// Windows 7, Server 2008 R2
		if (v->ServicePack <= 1)
		{
			// SP1 or earlier
			return true;
		}
	}

	if (v->VerMajor == 6 && v->VerMinor == 2)
	{
		// Windows 8, Server 2012
		if (v->ServicePack <= 0)
		{
			// SP0 only
			return true;
		}
	}

	if (v->VerMajor == 6 && v->VerMinor == 3)
	{
		// Windows 8.1, Server 2012 R2
		if (v->ServicePack <= 0)
		{
			// SP0 only
			return true;
		}
	}

	if ((v->VerMajor == 6 && v->VerMinor == 4) || (v->VerMajor == 10 && v->VerMinor == 0))
	{
		// Windows 10 or Windows Server 2016
		if (v->ServicePack <= 0)
		{
			// SP0 only
			return true;
		}
	}

	return false;
}