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
 int /*<<< orphan*/ * NewUDP (int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

bool SiCanOpenVpnOverDnsPort()
{
	// Whether UDP Port 53 can be listen on
	SOCK *s = NewUDP(53);

	if (s == NULL)
	{
		// Listening failure
		return false;
	}

	Disconnect(s);
	ReleaseSock(s);

	return true;
}