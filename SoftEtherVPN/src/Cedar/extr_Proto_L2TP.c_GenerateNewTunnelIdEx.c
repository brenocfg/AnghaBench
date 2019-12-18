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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/ * GetTunnelFromId (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

UINT GenerateNewTunnelIdEx(L2TP_SERVER *l2tp, IP *client_ip, bool is_32bit)
{
	UINT id;
	UINT max_number = 0xffff;
	// Validate arguments
	if (l2tp == NULL || client_ip == NULL)
	{
		return 0;
	}

	if (is_32bit)
	{
		max_number = 0xfffffffe;
	}

	for (id = 1;id <= max_number;id++)
	{
		if (GetTunnelFromId(l2tp, client_ip, id, is_32bit) == NULL)
		{
			return id;
		}
	}

	return 0;
}