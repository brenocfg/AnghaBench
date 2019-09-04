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
struct TYPE_3__ {int Masked; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ AC ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GSF_DISABLE_AC ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPAnd6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IPToUINT (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 

bool IsIpMaskedByAc(IP *ip, AC *ac)
{
	UINT uip, net, mask;
	// Validate arguments
	if (ip == NULL || ac == NULL)
	{
		return false;
	}

	if (GetGlobalServerFlag(GSF_DISABLE_AC) != 0)
	{
		return false;
	}

	if (IsIP4(ip))
	{
		// IPv4
		uip = IPToUINT(ip);
		net = IPToUINT(&ac->IpAddress);
		mask = IPToUINT(&ac->SubnetMask);

		if (ac->Masked == false)
		{
			if (uip == net)
			{
				return true;
			}
		}
		else
		{
			if ((uip & mask) == (net & mask))
			{
				return true;
			}
		}

		return false;
	}
	else
	{
		// IPv6
		if (ac->Masked == false)
		{
			if (CmpIpAddr(ip, &ac->IpAddress) == 0)
			{
				return true;
			}
		}
		else
		{
			IP and1, and2;

			IPAnd6(&and1, ip, &ac->SubnetMask);
			IPAnd6(&and2, &ac->IpAddress, &ac->SubnetMask);

			if (CmpIpAddr(&and1, &and2) == 0)
			{
				return true;
			}
		}

		return false;
	}
}