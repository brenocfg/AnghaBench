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
typedef  int /*<<< orphan*/  L2TP_SERVER ;

/* Variables and functions */
 int Rand32 () ; 
 int SearchL2TPSessionById (int /*<<< orphan*/ *,int,int) ; 

UINT GenerateNewSessionIdForL2TPv3(L2TP_SERVER *l2tp)
{
	// Validate arguments
	if (l2tp == NULL)
	{
		return 0;
	}

	while (true)
	{
		UINT id = Rand32();

		if (id == 0 || id == 0xffffffff)
		{
			continue;
		}

		if (SearchL2TPSessionById(l2tp, true, id) == false)
		{
			return id;
		}
	}
}