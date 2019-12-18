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
typedef  int u_int8_t ;

/* Variables and functions */
#define  IFRTYPE_FUNCTIONAL_INTCOPROC 129 
#define  IFRTYPE_FUNCTIONAL_WIFI_AWDL 128 

__attribute__((used)) static bool
necp_interface_type_is_primary_eligible(u_int8_t interface_type)
{
	switch (interface_type) {
		// These types can never be primary, so a client requesting these types is allowed
		// to match an interface that isn't currently eligible to be primary (has default
		// route, dns, etc)
		case IFRTYPE_FUNCTIONAL_WIFI_AWDL:
		case IFRTYPE_FUNCTIONAL_INTCOPROC:
			return false;
		default:
			break;
	}
	return true;
}