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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT ;
struct TYPE_3__ {int PlainTextMode; scalar_t__ IsIPv6; } ;
typedef  TYPE_1__ UDP_ACCEL ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int MTU_FOR_PPPOE ; 
 scalar_t__ UDP_ACCELERATION_PACKET_IV_SIZE ; 

UINT UdpAccelCalcMss(UDP_ACCEL *a)
{
	UINT ret;

	// Validate arguments
	if (a == NULL)
	{
		return 0;
	}

	ret = MTU_FOR_PPPOE;

	// IPv4
	if (a->IsIPv6)
	{
		ret -= 40;
	}
	else
	{
		ret -= 20;
	}

	// UDP
	ret -= 8;

	if (a->PlainTextMode == false)
	{
		// IV
		ret -= UDP_ACCELERATION_PACKET_IV_SIZE;
	}

	// Cookie
	ret -= sizeof(UINT);

	// My Tick
	ret -= sizeof(UINT64);

	// Your Tick
	ret -= sizeof(UINT64);

	// Size
	ret -= sizeof(USHORT);

	// Compress Flag
	ret -= sizeof(UCHAR);

	if (a->PlainTextMode == false)
	{
		// Verify
		ret -= UDP_ACCELERATION_PACKET_IV_SIZE;
	}

	// Ethernet header (communication packets)
	ret -= 14;

	// IPv4 Header (communication packets)
	ret -= 20;

	// TCP header (communication packet)
	ret -= 20;

	return ret;
}