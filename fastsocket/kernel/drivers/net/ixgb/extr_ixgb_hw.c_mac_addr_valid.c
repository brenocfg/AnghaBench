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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ IS_BROADCAST (scalar_t__*) ; 
 scalar_t__ IS_MULTICAST (scalar_t__*) ; 

__attribute__((used)) static bool
mac_addr_valid(u8 *mac_addr)
{
	bool is_valid = true;
	DEBUGFUNC("mac_addr_valid");

	/* Make sure it is not a multicast address */
	if (IS_MULTICAST(mac_addr)) {
		DEBUGOUT("MAC address is multicast\n");
		is_valid = false;
	}
	/* Not a broadcast address */
	else if (IS_BROADCAST(mac_addr)) {
		DEBUGOUT("MAC address is broadcast\n");
		is_valid = false;
	}
	/* Reject the zero address */
	else if (mac_addr[0] == 0 &&
			 mac_addr[1] == 0 &&
			 mac_addr[2] == 0 &&
			 mac_addr[3] == 0 &&
			 mac_addr[4] == 0 &&
			 mac_addr[5] == 0) {
		DEBUGOUT("MAC address is all zeros\n");
		is_valid = false;
	}
	return (is_valid);
}