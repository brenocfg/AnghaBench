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
struct TYPE_2__ {int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  ClientIP; } ;
typedef  TYPE_1__ IKE_CLIENT ;

/* Variables and functions */
 int COMPARE_RET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CmpIkeClient(void *p1, void *p2)
{
	IKE_CLIENT *c1, *c2;
	int r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	c1 = *(IKE_CLIENT **)p1;
	c2 = *(IKE_CLIENT **)p2;
	if (c1 == NULL || c2 == NULL)
	{
		return 0;
	}

	r = CmpIpAddr(&c1->ClientIP, &c2->ClientIP);
	if (r != 0)
	{
		return r;
	}

	r = CmpIpAddr(&c1->ServerIP, &c2->ServerIP);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(c1->ClientPort, c2->ClientPort);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(c1->ServerPort, c2->ServerPort);
	if (r != 0)
	{
		return r;
	}

	return 0;
}