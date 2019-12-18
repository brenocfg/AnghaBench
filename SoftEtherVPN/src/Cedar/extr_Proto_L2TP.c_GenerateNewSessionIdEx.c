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
typedef  int /*<<< orphan*/  L2TP_TUNNEL ;

/* Variables and functions */
 int /*<<< orphan*/ * GetSessionFromId (int /*<<< orphan*/ *,int) ; 

UINT GenerateNewSessionIdEx(L2TP_TUNNEL *t, bool is_32bit)
{
	UINT i;
	UINT max_number = 0xffff;
	// Validate arguments
	if (t == NULL)
	{
		return 0;
	}

	if (is_32bit)
	{
		max_number = 0xfffffffe;
	}

	for (i = 1;i <= max_number;i++)
	{
		if (GetSessionFromId(t, i) == NULL)
		{
			return i;
		}
	}

	return 0;
}