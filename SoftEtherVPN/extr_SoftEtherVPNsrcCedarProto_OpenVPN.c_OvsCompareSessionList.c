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
struct TYPE_2__ {int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  Protocol; } ;
typedef  TYPE_1__ OPENVPN_SESSION ;

/* Variables and functions */
 int COMPARE_RET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OvsCompareSessionList(void *p1, void *p2)
{
	OPENVPN_SESSION *s1, *s2;
	int i;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	s1 = *(OPENVPN_SESSION **)p1;
	s2 = *(OPENVPN_SESSION **)p2;
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}

	i = CmpIpAddr(&s1->Protocol, &s2->Protocol);
	if (i != 0)
	{
		return i;
	}

	i = CmpIpAddr(&s1->ClientIp, &s2->ClientIp);
	if (i != 0)
	{
		return i;
	}

	i = COMPARE_RET(s1->ClientPort, s2->ClientPort);
	if (i != 0)
	{
		return i;
	}

	i = CmpIpAddr(&s1->ServerIp, &s2->ServerIp);
	if (i != 0)
	{
		return i;
	}

	i = COMPARE_RET(s1->ServerPort, s2->ServerPort);
	if (i != 0)
	{
		return i;
	}

	return 0;
}