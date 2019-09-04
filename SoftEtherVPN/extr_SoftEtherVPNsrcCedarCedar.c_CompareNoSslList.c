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
struct TYPE_2__ {int /*<<< orphan*/  IpAddress; } ;
typedef  TYPE_1__ NON_SSL ;

/* Variables and functions */
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CompareNoSslList(void *p1, void *p2)
{
	NON_SSL *n1, *n2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	n1 = *(NON_SSL **)p1;
	n2 = *(NON_SSL **)p2;
	if (n1 == NULL || n2 == NULL)
	{
		return 0;
	}
	return CmpIpAddr(&n1->IpAddress, &n2->IpAddress);
}