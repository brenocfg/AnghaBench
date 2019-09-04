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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int* ipv6_addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GenerateEui64Address6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroIP6 (TYPE_1__*) ; 

void GenerateEui64LocalAddress(IP *a, UCHAR *mac)
{
	UCHAR tmp[8];
	// Validate arguments
	if (a == NULL || mac == NULL)
	{
		return;
	}

	GenerateEui64Address6(tmp, mac);

	ZeroIP6(a);
	a->ipv6_addr[0] = 0xfe;
	a->ipv6_addr[1] = 0x80;

	Copy(&a->ipv6_addr[8], tmp, 8);
}