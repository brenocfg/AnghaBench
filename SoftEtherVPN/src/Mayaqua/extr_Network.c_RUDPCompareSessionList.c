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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  MyPort; int /*<<< orphan*/  MyIp; int /*<<< orphan*/  YourPort; int /*<<< orphan*/  YourIp; } ;
typedef  TYPE_1__ RUDP_SESSION ;

/* Variables and functions */
 scalar_t__ COMPARE_RET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int RUDPCompareSessionList(void *p1, void *p2)
{
	RUDP_SESSION *s1, *s2;
	UINT r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	s1 = *((RUDP_SESSION **)p1);
	s2 = *((RUDP_SESSION **)p2);
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}

	r = CmpIpAddr(&s1->YourIp, &s2->YourIp);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(s1->YourPort, s2->YourPort);
	if (r != 0)
	{
		return r;
	}

	r = CmpIpAddr(&s1->MyIp, &s2->MyIp);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(s1->MyPort, s2->MyPort);
	if (r != 0)
	{
		return r;
	}

	return 0;
}