#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int* addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,int,int,int,int) ; 

void IPToStr4(char *str, UINT size, IP *ip)
{
	// Validate arguments
	if (str == NULL || ip == NULL)
	{
		return;
	}

	// Conversion
	snprintf(str, size != 0 ? size : 64, "%u.%u.%u.%u", ip->addr[0], ip->addr[1], ip->addr[2], ip->addr[3]);
}