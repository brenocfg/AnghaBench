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
typedef  int u_char ;
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/ * sa_data; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
#define  AF_LINK 129 
#define  AF_UNSPEC 128 
 int* CONST_LLADDR (struct sockaddr_dl const*) ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 

errno_t
ether_check_multi(ifnet_t ifp, const struct sockaddr *proto_addr)
{
#pragma unused(ifp)
	errno_t	result = EAFNOSUPPORT;
	const u_char *e_addr;

	/*
	 * AF_SPEC and AF_LINK don't require translation. We do
	 * want to verify that they specify a valid multicast.
	 */
	switch(proto_addr->sa_family) {
	case AF_UNSPEC:
		e_addr = (const u_char*)&proto_addr->sa_data[0];
		if ((e_addr[0] & 0x01) != 0x01)
			result = EADDRNOTAVAIL;
		else
			result = 0;
		break;

	case AF_LINK:
		e_addr = CONST_LLADDR((const struct sockaddr_dl*)
		    (uintptr_t)(size_t)proto_addr);
		if ((e_addr[0] & 0x01) != 0x01)
			result = EADDRNOTAVAIL;
		else
			result = 0;
		break;
	}

	return (result);
}