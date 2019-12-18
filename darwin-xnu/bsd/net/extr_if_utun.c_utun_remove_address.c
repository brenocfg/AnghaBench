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
struct sockaddr {int dummy; } ;
struct in6_ifreq {struct sockaddr ifr_addr; int /*<<< orphan*/  ifr_name; } ;
struct ifreq {struct sockaddr ifr_addr; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/  ifr6 ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  ifaddr_t ;
typedef  int errno_t ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  SIOCDIFADDR ; 
 int /*<<< orphan*/  SIOCDIFADDR_IN6 ; 
 int /*<<< orphan*/  bzero (struct in6_ifreq*,int) ; 
 int ifaddr_address (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 char* ifnet_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int sock_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_ifreq*) ; 

__attribute__((used)) static void
utun_remove_address(ifnet_t interface,
					protocol_family_t protocol,
					ifaddr_t address,
					socket_t pf_socket)
{
	errno_t result = 0;
	
	/* Attempt a detach */
	if (protocol == PF_INET) {
		struct ifreq ifr;
		
		bzero(&ifr, sizeof(ifr));
		snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s%d",
				 ifnet_name(interface), ifnet_unit(interface));
		result = ifaddr_address(address, &ifr.ifr_addr, sizeof(ifr.ifr_addr));
		if (result != 0) {
			printf("utun_remove_address - ifaddr_address failed: %d", result);
		} else {
			result = sock_ioctl(pf_socket, SIOCDIFADDR, &ifr);
			if (result != 0) {
				printf("utun_remove_address - SIOCDIFADDR failed: %d", result);
			}
		}
	} else if (protocol == PF_INET6) {
		struct in6_ifreq ifr6;
		
		bzero(&ifr6, sizeof(ifr6));
		snprintf(ifr6.ifr_name, sizeof(ifr6.ifr_name), "%s%d",
				 ifnet_name(interface), ifnet_unit(interface));
		result = ifaddr_address(address, (struct sockaddr*)&ifr6.ifr_addr,
								sizeof(ifr6.ifr_addr));
		if (result != 0) {
			printf("utun_remove_address - ifaddr_address failed (v6): %d",
				   result);
		} else {
			result = sock_ioctl(pf_socket, SIOCDIFADDR_IN6, &ifr6);
			if (result != 0) {
				printf("utun_remove_address - SIOCDIFADDR_IN6 failed: %d",
					   result);
			}
		}
	}
}