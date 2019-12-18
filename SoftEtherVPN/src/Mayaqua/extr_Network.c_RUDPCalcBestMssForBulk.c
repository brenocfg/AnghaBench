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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT ;
struct TYPE_6__ {int /*<<< orphan*/  YourIp; } ;
struct TYPE_5__ {scalar_t__ Protocol; } ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_2__ RUDP_SESSION ;

/* Variables and functions */
 int IsIP6 (int /*<<< orphan*/ *) ; 
 int MTU_FOR_PPPOE ; 
 scalar_t__ RUDP_PROTOCOL_DNS ; 
 scalar_t__ RUDP_PROTOCOL_ICMP ; 
 scalar_t__ SHA1_SIZE ; 

UINT RUDPCalcBestMssForBulk(RUDP_STACK *r, RUDP_SESSION *se)
{
	UINT ret;
	// Validate arguments
	if (r == NULL || se == NULL)
	{
		return 0;
	}

	ret = MTU_FOR_PPPOE;

	// IPv4
	if (IsIP6(&se->YourIp) == false)
	{
		ret -= 20;
	}
	else
	{
		ret -= 40;
	}

	if (r->Protocol == RUDP_PROTOCOL_ICMP)
	{
		// ICMP
		ret -= 8;

		ret -= SHA1_SIZE;
	}
	else if (r->Protocol == RUDP_PROTOCOL_DNS)
	{
		// UDP
		ret -= 8;

		// DNS
		ret -= 42;
	}

	// IV
	ret -= SHA1_SIZE;

	// Sign
	ret -= SHA1_SIZE;

	// SEQ_NO
	ret -= sizeof(UINT64);

	// Padding Max
	ret -= 31;

	// Ethernet header (target packets of communication)
	ret -= 14;

	// IPv4 Header (target packet of communication)
	ret -= 20;

	// TCP header (target packet of communication)
	ret -= 20;

	// I don't know well, but subtract 24 bytes
	ret -= 24;

	return ret;
}