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
typedef  int UINT ;
struct TYPE_3__ {int CryptBlockSize; int /*<<< orphan*/  ClientIP; scalar_t__ IsTunnelMode; } ;
typedef  TYPE_1__ ETHERIP_SERVER ;

/* Variables and functions */
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int MTU_FOR_PPPOE ; 

UINT CalcEtherIPTcpMss(ETHERIP_SERVER *s)
{
	UINT ret = MTU_FOR_PPPOE;
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	// IPv4 / IPv6
	if (IsIP4(&s->ClientIP))
	{
		ret -= 20;
	}
	else
	{
		ret -= 40;
	}

	// IPsec UDP
	ret -= 8;

	// IPsec ESP
	ret -= 20;
	ret -= s->CryptBlockSize * 2;

	// IPsec Tunnel Mode IPv4 / IPv6 Header
	if (s->IsTunnelMode)
	{
		if (IsIP4(&s->ClientIP))
		{
			ret -= 20;
		}
		else
		{
			ret -= 40;
		}
	}

	// EtherIP, L2TPv3
	ret -= 2;

	// Ethernet
	ret -= 14;

	// IPv4
	ret -= 20;

	// TCP
	ret -= 20;

	return ret;
}