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
typedef  int UINT ;
typedef  int /*<<< orphan*/  IKE_SERVER ;

/* Variables and functions */
 int INFINITE ; 
 int Rand32 () ; 
 int /*<<< orphan*/ * SearchClientToServerIPsecSaBySpi (int /*<<< orphan*/ *,int) ; 

UINT GenerateNewIPsecSaSpi(IKE_SERVER *ike, UINT counterpart_spi)
{
	UINT ret;
	// Validate arguments
	if (ike == NULL)
	{
		return 0;
	}

	while (true)
	{
		ret = Rand32();

		if (ret != counterpart_spi)
		{
			if (ret >= 4096 && ret != INFINITE)
			{
				if (SearchClientToServerIPsecSaBySpi(ike, ret) == NULL)
				{
					return ret;
				}
			}
		}
	}
}