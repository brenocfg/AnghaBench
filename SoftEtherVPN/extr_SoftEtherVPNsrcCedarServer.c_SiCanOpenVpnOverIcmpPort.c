#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 int /*<<< orphan*/  MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewUDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

bool SiCanOpenVpnOverIcmpPort()
{
	// Whether the ICMP can be opened
	SOCK *s = NewUDP(MAKE_SPECIAL_PORT(IP_PROTO_ICMPV4));

	if (s == NULL)
	{
		// Failure
		return false;
	}

	Disconnect(s);
	ReleaseSock(s);

	return true;
}