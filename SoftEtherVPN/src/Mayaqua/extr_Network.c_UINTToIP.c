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
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroIP4 (TYPE_1__*) ; 

void UINTToIP(IP *ip, UINT value)
{
	UCHAR *b;
	UINT i;
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	ZeroIP4(ip);

	b = (UCHAR *)&value;
	for (i = 0;i < 4;i++)
	{
		ip->addr[i] = b[i];
	}
}