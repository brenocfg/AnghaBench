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
struct TYPE_2__ {scalar_t__ Port; scalar_t__ Udp; } ;
typedef  TYPE_1__ NETSVC ;

/* Variables and functions */

int CompareNetSvc(void *p1, void *p2)
{
	NETSVC *n1, *n2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	n1 = *(NETSVC **)p1;
	n2 = *(NETSVC **)p2;
	if (n1 == NULL || n2 == NULL)
	{
		return 0;
	}
	if (n1->Port > n2->Port)
	{
		return 1;
	}
	else if (n1->Port < n2->Port)
	{
		return -1;
	}
	else if (n1->Udp > n2->Udp)
	{
		return 1;
	}
	else if (n1->Udp < n2->Udp)
	{
		return -1;
	}
	return 0;
}