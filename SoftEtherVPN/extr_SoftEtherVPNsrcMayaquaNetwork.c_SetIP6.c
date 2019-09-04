#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int* addr; int /*<<< orphan*/ * ipv6_addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SetIP6(IP *ip, UCHAR *value)
{
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	Zero(ip, sizeof(IP));

	ip->addr[0] = 223;
	ip->addr[1] = 255;
	ip->addr[2] = 255;
	ip->addr[3] = 254;

	if (value != NULL)
	{
		UINT i;

		for (i = 0;i < 16;i++)
		{
			ip->ipv6_addr[i] = value[i];
		}
	}
}