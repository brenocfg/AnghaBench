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
struct in6_ifreq {int /*<<< orphan*/  ifr_name; } ;
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/  ifr6 ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  SIOCPROTODETACH ; 
 int /*<<< orphan*/  SIOCPROTODETACH_IN6 ; 
 int /*<<< orphan*/  bzero (struct in6_ifreq*,int) ; 
 char* ifnet_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_ifreq*) ; 

__attribute__((used)) static errno_t
ipsec_detach_ip(ifnet_t				interface,
				protocol_family_t	protocol,
				socket_t			pf_socket)
{
	errno_t result = EPROTONOSUPPORT;
	
	/* Attempt a detach */
	if (protocol == PF_INET) {
		struct ifreq	ifr;
		
		bzero(&ifr, sizeof(ifr));
		snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s%d",
				 ifnet_name(interface), ifnet_unit(interface));
		
		result = sock_ioctl(pf_socket, SIOCPROTODETACH, &ifr);
	}
	else if (protocol == PF_INET6) {
		struct in6_ifreq	ifr6;
		
		bzero(&ifr6, sizeof(ifr6));
		snprintf(ifr6.ifr_name, sizeof(ifr6.ifr_name), "%s%d",
				 ifnet_name(interface), ifnet_unit(interface));
		
		result = sock_ioctl(pf_socket, SIOCPROTODETACH_IN6, &ifr6);
	}
	
	return result;
}