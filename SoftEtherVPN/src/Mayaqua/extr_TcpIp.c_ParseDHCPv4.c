#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * DHCPv4Header; } ;
struct TYPE_5__ {int /*<<< orphan*/  TypeL7; TYPE_1__ L7; } ;
typedef  TYPE_2__ PKT ;
typedef  int /*<<< orphan*/  DHCPV4_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  L7_DHCPV4 ; 

void ParseDHCPv4(PKT *p, UCHAR *buf, UINT size)
{
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return;
	}

	// Check the size
	if (size < sizeof(DHCPV4_HEADER))
	{
		// Size is invalid
		return;
	}

	// DHCPv4 header
	p->L7.DHCPv4Header = (DHCPV4_HEADER *)buf;
	p->TypeL7 = L7_DHCPV4;
}