#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {int CryptBlockSize; scalar_t__ IsIPsecIPv6; int /*<<< orphan*/ * IkeServer; } ;
struct TYPE_5__ {int /*<<< orphan*/  ClientIp; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  int /*<<< orphan*/  L2TP_SESSION ;
typedef  TYPE_2__ L2TP_SERVER ;

/* Variables and functions */
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int MTU_FOR_PPPOE ; 

UINT CalcL2TPMss(L2TP_SERVER *l2tp, L2TP_TUNNEL *t, L2TP_SESSION *s)
{
	UINT ret;
	// Validate arguments
	if (l2tp == NULL || t == NULL || s == NULL)
	{
		return 0;
	}

	ret = MTU_FOR_PPPOE;

	if (l2tp->IkeServer != NULL)
	{
		// On IPsec
		if (l2tp->IsIPsecIPv6)
		{
			ret -= 40;
		}
		else
		{
			ret -= 20;
		}

		// UDP
		ret -= 8;

		// ESP
		ret -= 20 + l2tp->CryptBlockSize * 2;
	}
	else
	{
		// Raw L2TP
		if (IsIP6(&t->ClientIp))
		{
			ret -= 40;
		}
		else
		{
			ret -= 20;
		}
	}

	// L2TP UDP
	ret -= 8;

	// L2TP
	ret -= 8;

	// PPP
	ret -= 4;

	// Target communication
	ret -= 20;

	// TCP header
	ret -= 20;

	return ret;
}