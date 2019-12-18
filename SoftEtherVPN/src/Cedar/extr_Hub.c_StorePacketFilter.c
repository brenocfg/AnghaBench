#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Hub; } ;
typedef  TYPE_1__ SESSION ;
typedef  int /*<<< orphan*/  PKT ;

/* Variables and functions */
 int ApplyAccessListToStoredPacket (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int StorePacketFilterByPolicy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int StorePacketFilterByTrafficLimiter (TYPE_1__*,int /*<<< orphan*/ *) ; 

bool StorePacketFilter(SESSION *s, PKT *packet)
{
	// Validate arguments
	if (s == NULL || packet == NULL)
	{
		return false;
	}

	// The bandwidth reduction by traffic limiter
	if (StorePacketFilterByTrafficLimiter(s, packet) == false)
	{
		return false;
	}

	// Packet filter by policy
	if (StorePacketFilterByPolicy(s, packet) == false)
	{
		return false;
	}

	// The packet filter with Access Lists
	if (ApplyAccessListToStoredPacket(s->Hub, s, packet) == false)
	{
		return false;
	}

	return true;
}