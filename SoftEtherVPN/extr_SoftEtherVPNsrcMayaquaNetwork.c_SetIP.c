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
typedef  void* UCHAR ;
struct TYPE_4__ {void** addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SetIP(IP *ip, UCHAR a1, UCHAR a2, UCHAR a3, UCHAR a4)
{
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	Zero(ip, sizeof(IP));
	ip->addr[0] = a1;
	ip->addr[1] = a2;
	ip->addr[2] = a3;
	ip->addr[3] = a4;
}